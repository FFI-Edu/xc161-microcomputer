#include "mcpr_xc161_timer.h"

uint32 timer_count = 0;

void timer_init() {
	// TIMER 6
	GPT12E_CAPREL     = 0xF680;
	GPT12E_T6CON_T6UD = 0; // Aufwärts
	GPT12E_T6CON		 |= 2; // Prescaler 16
	GPT12E_T6CON_T6R 	= 1; // An
	GPT12E_T6CON_T6SR = 1; // Reload aktiv
  GPT12E_T6IC_IE		= 1; // Interrupt Enable
	GPT12E_T6IC			 |= 8; // Mittlere Prio
	// TIMER 3
	GPT12E_CAPREL     = 0xF680;
	GPT12E_T3CON_T3UD = 0; // Aufwärts
	GPT12E_T3CON		 |= 8; // Counter Modus
	GPT12E_T3CON		 |= 1; // T3I
	GPT12E_T3CON_T3R 	= 1; // An
  GPT12E_T3IC_IE		= 1; // Interrupt Enable
	GPT12E_T3IC			 |= 8; // Mittlere Prio
}

void t3_i() interrupt 0x26 {
	timer_count++;
}

