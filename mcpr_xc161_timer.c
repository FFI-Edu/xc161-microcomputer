#include "mcpr_xc161_timer.h"

uint32 timer_main  = 0;
uint32 timer_back  = 0;
uint32 timer_freq  = 0;
uint32 timer_temp  = 0;
  
void timer_init() {
	// CAPREL Register
	GPT12E_CAPREL     = 0xF63C; // 63036
 	
	// TIMER 6
	GPT12E_T6CON  |= 0x8042; // 1000000001000010	
	GPT12E_T6IC_IE = 1; // T6 Interrupt Enable
	GPT12E_T6IC	  |= 8; // T6 Mittlere Prio
	// TIMER 3 (TEMP)
}

void gpt1_cycle() {
	// TIMER 3
	GPT12E_T3CON = 0x0849; // 0000100001001001	
	DP3_P6		 = 0;      // T3IN
}

void gpt1_temp() {
	// TIMER 3 ( TIMER )	// 0000100001000000	
	GPT12E_T3CON   = 0x0840;
    DP3_P6		   = 0;     // T3IN
	GPT12E_T3IC_IE = 1;     // T6 Interrupt Enable
	GPT12E_T3IC	  |= 0xB;   // T6 Hohe Prio
	// TIMER 2 ( CAPTURE )	// 0000000001101001	
	GPT12E_T2CON = 0x0069;
	DP3_P5		 = 0;
	// TIMER 4 ( CAPTURE )	// 0000000001101001	
	GPT12E_T4CON = 0x0069;
	DP3_P3		 = 0;
}

void t6_i() interrupt 0x26 {
	timer_main++;
	timer_back++;
	timer_freq++;
	timer_temp++;
}

void t3_i() interrupt 0x23 {
}

/*GPT12E_T6CON_T6UD = 0; // Aufwärts
	GPT12E_T6CON		 |= 2; // Prescaler 16
	GPT12E_T6CON_T6R 	= 1; // An
	GPT12E_T6CON_T6SR = 1; // Reload aktiv*/

/*GPT12E_T3CON_T3UD = 0; // Aufwärts
	GPT12E_T3CON		 |= 8; // Counter Modus
	GPT12E_T3CON		 |= 1; // T3I
	GPT12E_T3CON_T3R 	= 1; // An*/

uint32 get_cycle() {	
  uint32 cycle     = 0;
  uint32 timer_end = 0;
	
  gpt1_cycle();
       
  timer_freq = 0;
  timer_end  = timer_freq + 100;
       
  while( timer_freq == 0 )
    GPT12E_T3 = 0;
       
  while( timer_end > timer_freq );
 
  cycle = GPT12E_T3;
               
  return (cycle * 10);
}

uint16 get_temp() {
	uint16 temp = 0;
	uint16 wert1;
	uint16 wert2;
	gpt1_temp();
	
	// IC2Q7 => 1
	IC2 = 0x80;
	// Warten bis T4IN = 1
	while( T4IN != 1 );
	// Warten (1 ms)
	wait(100);
	// IC2Q7 => 0
	IC2 = 0x00;
	// Warten bis T4IN = 0
	while( T4IN != 0 );
	// Zeit Messen
	wert1 = GPT12E_T4;
	// Bis T2IN = 0
	while( T2IN != 0 );
	
	wert2 = GPT12E_T2;
	temp = wert1 - wert2;
	temp = (temp-1200)>>2;
	
	return temp;
}