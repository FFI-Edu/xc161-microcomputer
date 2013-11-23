#ifndef _TIMER_H_
#define _TIMER_H_

#include <XC161.h>
#include "Platform_types.h"

extern uint32 timer_count;

void timer_init();
void t3_i();

#endif