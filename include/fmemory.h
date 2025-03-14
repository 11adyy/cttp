#ifndef _H_FMEMORY
#define _H_FMEMORY

#include <stdlib.h>
#include <string.h>
#include <immintrin.h>


void* __f_memcpy(void *dest, const void *src, size_t n);
void* __f_memset(void *dest, int c, size_t n);

#endif