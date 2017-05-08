// platform
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// header
#include <lock_pl.h>

typedef struct Lock_pl_t
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} Lock_pl_t;

void LOCK_PL_init(void **handle)
{
	Lock_pl_t *lock = (Lock_pl_t *)malloc(sizeof(Lock_pl_t));

	// mutex init
	pthread_mutex_init(&lock->mutex, NULL);
	// condition init
	pthread_cond_init(&lock->cond, NULL);
	// set outContext
	*handle = lock;

	return;
}

void LOCK_PL_lock(void *inHandle)
{
	Lock_pl_t *lock = (Lock_pl_t *)inHandle;
	pthread_mutex_lock(&lock->mutex);
}


void LOCK_PL_unlock(void *inHandle)
{
	Lock_pl_t *lock = (Lock_pl_t *)inHandle;
	pthread_mutex_unlock(&lock->mutex);
}

void LOCK_PL_signal(void *inHandle)
{
	Lock_pl_t *lock = (Lock_pl_t *)inHandle;
	pthread_cond_signal(&lock->cond);
}

void LOCK_PL_wait(void *inHandle)
{
	Lock_pl_t *lock = (Lock_pl_t *)inHandle;
	pthread_cond_wait(&lock->cond, &lock->mutex);
}

void LOCK_PL_term(void *inHandle)
{
	Lock_pl_t *lock = (Lock_pl_t *)inHandle;
	pthread_mutex_destroy(&lock->mutex);
	pthread_cond_destroy(&lock->cond);
}
