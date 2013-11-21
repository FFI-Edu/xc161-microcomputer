#include <XC161.h>
#include "Platform_types.h"
 
#define IC2 (*((uint8*) 0x100002))
#define IC3 (*((uint8*) 0x100004))
 
void lcd_backlight (uint8 state);
void led_output (uint8 led);
void lcd_backlight_controller(
				uint16 ks, 
				uint8* lkey_state_up, 
				uint8* lkey_state_down, 
				uint8* last_lcd
			     );
uint16 read_keys();
 
/****************/
/*     main     */
/****************/     
void main (void) {
       
        uint16 key_state;
        uint8 tmp                 = 0;
        uint16 no_key             = 0x0000;
	
				uint8 last_key_state_up   = 0x00;
				uint8 last_key_state_down = 0x00;
				uint8 last_lcd_set        = 0x00; //only last 2 bits important
       
        while(1) {
                key_state = read_keys();
                tmp=((uint8) key_state)  |  ((uint8) (key_state>>8));
                led_output(tmp);
                lcd_backlight_controller(
					key_state, 
					&last_key_state_up, 
					&last_key_state_down, 
					&last_lcd_set
					);          
        }
}
 
void lcd_backlight_controller(
			       	uint16 ks, 
				uint8* lkey_state_up, 
				uint8* lkey_state_down, 
				uint8* last_lcd
			     ){
																
        uint8 nkey_state_up   = ((uint8) ks);
        uint8 nkey_state_down = ((uint8) (ks>>8));
        if( nkey_state_up > *lkey_state_up ){
                if( (*last_lcd & 0x01) > 0 ){
                        lcd_backlight(0);
                        *last_lcd = *last_lcd & (~0x01);
                }else{
                        lcd_backlight(1);
                        *last_lcd = *last_lcd | 0x01;
                }
        }
        if( nkey_state_down < *lkey_state_down ){
                if( (*last_lcd & 0x02) > 0 ){
                        lcd_backlight(0);
                        *last_lcd = *last_lcd & (~0x02);
                }else{
                        lcd_backlight(1);
                        *last_lcd = *last_lcd | 0x02;
                }
        }
				*lkey_state_up   = nkey_state_up;
        *lkey_state_down = nkey_state_down;
				
}
 
void lcd_backlight (uint8 state) {
        DP7       =     0x00F0;
        P7_P4 = state;
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
               
                for(j=0; j<100; j++); //auf Transistoren warten
               
                state = state<<4;
                state |= ~(P5) & 0xF;
        }
       
        return state;
}