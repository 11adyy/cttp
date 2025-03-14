#include "../include/fmemory.h"


void* __f_memcpy(void *dest, const void *src, size_t n) {
    __m256i *d = (__m256i *)dest;
    const __m256i *s = (const __m256i *)src;
    size_t i;
    for (i = 0; i < n / 32; i++) {
        _mm256_storeu_si256(&d[i], _mm256_loadu_si256(&s[i]));
    }
    
    uint8_t *dest_bytes = (uint8_t *)dest + i * 32;
    const uint8_t *src_bytes = (const uint8_t *)src + i * 32;
    for (size_t j = 0; j < n % 32; j++) {
        dest_bytes[j] = src_bytes[j];
    }
    
    return dest;
}

void* __f_memset(void *dest, int c, size_t n) {
    __m256i val = _mm256_set1_epi8((char)c);
    __m256i *d = (__m256i *)dest;
    for (size_t i = 0; i < n / 32; i++) {
        _mm256_storeu_si256(&d[i], val);
    }

    return dest;
}