#include<stdio.h>
#include<stdlib.h>

// application
#include <lock_pl.h>
#include <queue.h>

typedef struct QueueList_t
{
	void *head;
	void *tail;
	void *lock;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}QueueList_t;

typedef struct Entry_t
{
	void *data;
	struct Entry_t *next;
}Entry_t;

void QUEUE_init(void **handle)
{
	QueueList_t *queueList = (QueueList_t *)malloc(sizeof(QueueList_t));

	// init thread safe
	LOCK_PL_init(&queueList->lock);
	// initialize queue
	queueList->head = NULL;
	// points to the first element that exists in queue
	queueList->tail = &queueList->head;

	*handle = queueList;
	return;
}

void QUEUE_put(void *inHandle, void *inData)
{
	QueueList_t *queueList = (QueueList_t *)inHandle;
	Entry_t *newEntry = (Entry_t *)malloc(sizeof(Entry_t));

	newEntry->data = inData;
	newEntry->next = NULL;

	//	thread safe lock
	LOCK_PL_lock(queueList->lock);
	
	*((Entry_t **)queueList->tail) = newEntry;
	queueList->tail = &newEntry->next;

	// thread safe signal to handle the new event
	LOCK_PL_signal(queueList->lock);
	// unlock the thread for next event.
	LOCK_PL_unlock(queueList->lock);
}

void *QUEUE_get(void *inHandle)
{
	Entry_t * remove = NULL;
	QueueList_t *queueList = (QueueList_t *)inHandle;
	void *retData;

	// thread safe lock
	LOCK_PL_lock(queueList->lock);

	remove = queueList->head;
	if (remove != NULL)
		queueList->head = remove->next;

	/* if the queue got empty, initialize the tail */
	if (!queueList->head)
	{
		queueList->tail = &queueList->head;
	}

	retData = remove->data;

	//	thread safe unlcok 
	LOCK_PL_unlock(queueList->lock);
	// remove the entry memory
	free(remove);
	return retData;
}

void QUEUE_wait(void *inHandle)
{
	QueueList_t *queueList = (QueueList_t *)inHandle;
	// thread safe wait for signal to start handling the event
	LOCK_PL_wait(queueList->lock);
	// thread safe unloack to handle the after signal
	LOCK_PL_unlock(queueList->lock);
}

void QUEUE_term(void *inHandle)
{
	QueueList_t *queueList = (QueueList_t *)inHandle;
	// destroy object 
	LOCK_PL_term(queueList->lock);
	free(queueList);
}
