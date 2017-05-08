#ifndef __LOCK_PL__
#define __LOCK_PL__

#ifdef __cplusplus
extern "C"
{
#endif

void LOCK_PL_init(void **handle);
void LOCK_PL_lock(void *inHandle);
void LOCK_PL_unlock(void *inHandle);
void LOCK_PL_signal(void *inHandle);
void LOCK_PL_wait(void *inHandle);
void LOCK_PL_term(void *handle);

#ifdef __cplusplus
}
#endif

#endif // __LOCK_PL__
