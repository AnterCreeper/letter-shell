#ifndef __STRING_H__
#define __STRING_H__

#include <stdarg.h>
#include "stdint.h"

void *memset(void *str, int c, size_t n);
void *memcpy(void *dest, const void * src, size_t n);

size_t strlen(const char *str);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

int vsnprintf(char *sbuf, size_t n, const char *format, va_list args);

#endif
