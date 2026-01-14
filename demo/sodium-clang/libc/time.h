#ifndef __TIME_H__
#define __TIME_H__

#include "stdint.h"

#define CLOCKS_PER_SEC  (50*1000000)

typedef uint32_t clock_t;
clock_t clock(); //return system tick in microsecond

#endif
