#include <stdio.h>
#include <pthread.h>
#include <queue.h>
#include <logger_pl.h>
#include <memory_pl.h>
#include <signal.h>

typedef struct Event_t
{
	int id;
	char *name;
}Event_t;

pthread_t g_eventThreadListener;
void * queueHandle;
#define END_LESS_LOOP 1

static void *eventListener(void *arg)
{
	Event_t *event;
	while (END_LESS_LOOP)
	{
		LOGGER_PL_log("Waiting to handle new event\n");

		QUEUE_wait(queueHandle);
		event = (Event_t *)QUEUE_get(queueHandle);
		LOGGER_PL_log("event: %d was handled\n", event->id);
		MEMORY_PL_free(event);
	}
	return NULL;
}

int main()
{
	int eventNumber;
	int isStop = 0;

	// init queue
	QUEUE_init(&queueHandle);
	LOGGER_PL_init(0);
	pthread_create(&g_eventThreadListener, NULL, &eventListener, NULL);

	while(isStop == 0)
	{
		Event_t *event;
		LOGGER_PL_log("Please give event number: \n");
		scanf("%d", &eventNumber);
		if (eventNumber ==0)
		{
			isStop = 1;
			continue;
		}

		event = (Event_t *)MEMORY_PL_malloc(sizeof(Event_t));
		event->id = eventNumber;
		event->name = NULL;

		QUEUE_put(queueHandle, event); 
	}

	pthread_kill(g_eventThreadListener, SIGTERM);
	LOGGER_PL_log("End of programm!!!!!!\n");
	LOGGER_PL_term();
	QUEUE_term(queueHandle);
	return 0;
}
