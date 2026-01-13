/*
  derived from printf-stdarg.c

  Copyright 2001, 2002 Georges Menie (www.menie.org)
  stdarg version contributed by Christian Ettinger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "stdint.h"
#include <stdarg.h>

static inline void printchar(char **str, char* finish, int c)
{
  if (*str != finish) {
    **str = c;
    ++(*str);
  }
}

#define PAD_RIGHT 1
#define PAD_ZERO  2

static int prints(char **out, char* finish, const char *string, int width, int pad)
{
  int pc = 0, padchar = ' ';

  if (width > 0) {
    int len = 0;
    const char *ptr;
    for (ptr = string; *ptr; ++ptr) ++len;
    if (len >= width) width = 0;
    else width -= len;
    if (pad & PAD_ZERO) padchar = '0';
  }
  if (!(pad & PAD_RIGHT)) {
    for ( ; width > 0 && *out != finish; --width) {
      printchar(out, finish, padchar);
      ++pc;
    }
  }
  for ( ; *string && *out != finish; ++string) {
    printchar(out, finish, *string);
    ++pc;
  }
  for ( ; width > 0 && *out != finish; --width) {
    printchar(out, finish, padchar);
    ++pc;
  }

  return pc;
}

/* the following should be enough for 32 bit integer */
#define PRINT_BUF_LEN 12

static int printi(char **out, char* finish, unsigned long i, int b, int sg, int width, int pad, int letbase)
{
  char print_buf[PRINT_BUF_LEN];
  char *s;
  int t, neg = 0, pc = 0;
  unsigned long u = i;

  if (i == 0) {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return prints(out, finish, print_buf, width, pad);
  }

  if (sg && b == 10 && i < 0) {
    neg = 1;
    u = -i;
  }

  s = print_buf + PRINT_BUF_LEN-1;
  *s = '\0';

  while (u) {
    t = u % b;
    if( t >= 10 )
      t += letbase - '0' - 10;
    *--s = t + '0';
    u /= b;
  }

  if (neg) {
    if (width && (pad & PAD_ZERO)) {
      printchar(out, finish, '-');
      ++pc;
      --width;
    }
    else {
      *--s = '-';
    }
  }

  return pc + prints(out, finish, s, width, pad);
}

int vsnprintf(char *sbuf, size_t n, const char *format, va_list args)
{
  int pc = 0;
  if (sbuf == NULL) return pc;
  char** out = &sbuf;

  int width, pad;
  for (char* finish = &sbuf[n-1]; *format != '\0' && *out != finish; ++format) {
    if (*format == '%') {
      ++format;
      if (*format == '\0') break;
      if (*format == '%') goto bypass;
      //format
      width = pad = 0;
      if (*format == '-') {
        ++format;
        pad = PAD_RIGHT;
      }
      while (*format == '0') {
        ++format;
        pad |= PAD_ZERO;
      }
      for ( ; *format >= '0' && *format <= '9'; ++format) {
        width *= 10;
        width += *format - '0';
      }
      //qualifier
      int qualifier = 0;
      if (*format == '\0') break;
      while (*format == 'l' || *format == 'L') {
        ++format;
        ++qualifier;
      }
      //type
      int base, sgn, let;
      if (*format == '\0') break;
      switch (*format) {
      case 's': //string
      {
        char *s = (char *)va_arg(args, size_t);
        pc += prints(out, finish, s?s:"(null)", width, pad);
        continue;
      }
      case 'c': //char
      {
        /* char are converted to int then pushed on the stack */
        char scr[2];
        scr[0] = (char)va_arg(args, int);
        scr[1] = '\0';
        pc += prints(out, finish, scr, width, pad);
        continue;
      }
      case 'x': //lowercase hexadecimal
        sgn = 0;
        let = 'a';
        base = 16;
        break;
      case 'X': //uppercase hexadecimal
        sgn = 0;
        let = 'A';
        base = 16;
        break;
      case 'u': //unsigned decimal
      case 'p': //pointer
        sgn = 0;
        let = 'a';
        base = 10;
        break;
      default:
      case 'd': //decimal
        sgn = 1;
        let = 'a';
        base = 10;
        break;
      //TODO float point support
        break;
      }
      //number
      unsigned long num;
      switch (qualifier) {
        default:
        case 0:
          num = sgn ? va_arg(args, int) : va_arg(args, unsigned int);
          break;
        case 1:
          num = sgn ? va_arg(args, long) : va_arg(args, unsigned long);
          break;
        /*
        case 2:
          num = sgn ? va_arg(args, long long) : va_arg(args, unsigned long long);
          break;
        */
      }
      pc += printi(out, finish, num, base, sgn, width, pad, let);
    }
    else {
    bypass:
      printchar(out, finish, *format);
      ++pc;
    }
  }

  if (out) **out = '\0';
  va_end(args);
  return pc;
}

int snprintf(char *sbuf, size_t n, const char *format, ...) {
  va_list arg;
  int done;

  va_start(arg, format);
  done = vsnprintf(sbuf, n, format, arg);
  va_end(arg);

  return done;
}
