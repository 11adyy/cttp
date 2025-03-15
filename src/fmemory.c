#include "../include/fmemory.h"


void* __f_memcpy(void *dest, const void *src, size_t n) {
    __m256i *d = (__m256i *)dest;
    const __m256i *s = (const __m256i *)src;
    size_t i = 0;
    for (i = 0; i < n / 32; i++) {
        _mm256_storeu_si256(&d[i], _mm256_loadu_si256(&s[i]));
    }
    
    unsigned char* dest_bytes = (unsigned char*)dest + i * 32;
    const unsigned char *src_bytes = (const unsigned char*)src + i * 32;
    for (size_t j = 0; j < n % 32; j++) {
        dest_bytes[j] = src_bytes[j];
    }
    
    return dest;
}

void* __f_memset(void *dest, int c, size_t n) {
    __m256i val = _mm256_set1_epi8((char)c);
    __m256i *d = (__m256i *)dest;
    size_t i = 0;
    for (i = 0; i < n / 32; i++) {
        _mm256_storeu_si256(&d[i], val);
    }

    unsigned char* dest_bytes = (unsigned char*)dest + i * 32;
    for (size_t j = 0; j < n % 32; j++) {
        dest_bytes[j] = (unsigned char)c;
    }

    return dest;
}