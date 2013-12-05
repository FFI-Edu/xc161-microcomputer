#ifndef _TIMER_H_
#define _TIMER_H_

#include <XC161.h>
#include "Platform_types.h"
#include "mcpr_xc161_lcd.h"

sbit T3IN = P3^6;
sbit T4IN = P3^5;
sbit T2IN = P3^3;

extern uint32 timer_main;
extern uint32 timer_back;
extern uint32 timer_freq;
extern uint32 timer_temp;

void timer_init();
void t6_i();
void t3_i();

void gpt1_cycle();
void gpt1_temp();

uint32 get_cycle();
uint16 get_temp();

#endif