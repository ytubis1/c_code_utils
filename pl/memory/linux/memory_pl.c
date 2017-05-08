// platform
#include<stdlib.h>

// header
#include <memory_pl.h>

void *MEMORY_PL_malloc(size_t size)
{
	return malloc(size);
}

void MEMORY_PL_free(void *p)
{
	free(p);
}
