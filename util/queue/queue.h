#ifndef __QUEUE__
#define __QUEUE__


#ifdef __cplusplus
extern "C"
{
#endif


void QUEUE_init(void **handle);
void QUEUE_wait();
void *QUEUE_get(void *inHandle);
void QUEUE_put(void *inHandle, void *inData);
void QUEUE_term(void *inHandle);

#ifdef __cplusplus
}
#endif

#endif // __QUEUE__
