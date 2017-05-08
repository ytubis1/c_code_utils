#ifndef __MEMORY_PL__
#define __MEMORY_PL__

#ifdef __cplusplus
extern "C"
{
#endif

void *MEMORY_PL_malloc(size_t size);
void MEMORY_PL_free(void *);

#define MEMORY_PL_freeCheckAndSetNull(x) \
	if (x) \
	{ \
		MEMORY_PL_free(x); \
		x = NULL; \
	}

#ifdef __cplusplus
}
#endif

#endif // __MEMORY_PL__
