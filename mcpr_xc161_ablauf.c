#include <XC161.h>
#include "Platform_types.h"
#include "mcpr_xc161_lcd.h"
#include "mcpr_xc161_timer.h"

void led_output (uint8 led);
uint16 read_keys();
 
                  /****************/
                  /*     main     */
                  /****************/     
void main (void) {
	 // ====================
   // BACKLIGHT CONTROLLER
   uint16 key_state;
   uint16 temperature        = 0;
   uint16 no_key             = 0;
   uint8 last_key_state_up   = 0;
   uint8 last_key_state_down = 0;
   //uint8 last_lcd_set        = 0; //only last 2 bits important
   // ====================
   // LOOPTIMER
   uint32 timer_start        = 0;
	
   // ====================
   // INIT
   PSW_IEN        = 1; // Interrupt enable	
   lcd_init();
   timer_init();
	
	 // ====================
	 // MAINLOOP
   while(1) {
	  timer_main  = 0;
      timer_start = timer_main;
		  
	  // GET KEYS
      key_state = read_keys();
      led_output(((uint8) key_state)  |  ((uint8) (key_state>>8)));
      // LCD BL
      lcd_backlight_controller(key_state, &last_key_state_up, &last_key_state_down/*, &last_lcd_set*/);
      // LCD TEXT
      lcd_writestatus(get_cycle(),get_temp());
			
			while((timer_start + 50) > timer_main);
   }
}
 
void led_output (uint8 led) {
   IC2 = led;
}
 
uint16 read_keys() {
   int i        =0, j=0;
   uint16 state = 0;
   DP7_P6  = 1;
   P7_P6   = 0;
   for(i=0; i<4; i++) {
      IC3 = 1 << i;
      for(j=0; j<100; j++);  //auf Transistoren warten
      state = state<<4;
      state |= ~(P5) & 0xF;
   }  
   return state;
}