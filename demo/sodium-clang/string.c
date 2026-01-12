#include "string.h"

void *memset(void *str, int c, size_t n) {
    char *d = str;
    int t = (n + 7) / 8;
    switch (n % 8) {
    case 0 : do { *d++ = c;
    case 7 :      *d++ = c;
    case 6 :      *d++ = c;
    case 5 :      *d++ = c;
    case 4 :      *d++ = c;
    case 3 :      *d++ = c;
    case 2 :      *d++ = c;
    case 1 :      *d++ = c;
    } while (--t > 0);
    }
    return str;
}

void *memcpy(void *dest, const void * src, size_t n) {
    char* pdst = dest;
    const char* psrc = src;
    int i = 0;
    while (i < n) {
        pdst[i] = psrc[i];
        i++;
    }
    return dest;
}

size_t strlen(const char *str) {
    const char *start = str;
    while (*str)
        str++;
    return str - start;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1) - (*(unsigned char *)s2);
}

int strncmp(const char *s1, const char *s2, size_t n) {
    if (n == 0) return 0;
    while (n-- != 0 && *s1 == *s2) {
        if (n == 0 || *s1 == '\0')
            break;
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1) - (*(unsigned char *)s2);
}
