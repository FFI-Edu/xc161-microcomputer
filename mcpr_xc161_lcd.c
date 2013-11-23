#include "mcpr_xc161_lcd.h"
#include <string.h>

uint32 lcd_on_until = 0;

void lcd_init() {
   wait(40000); //40ms warten nach power on
   lcd_write(0x0, 0x30);
   wait(5000);
   lcd_write(0x0, 0x30);
   wait(100);
   lcd_write(0x0, 0x30);
   wait(100);
   lcd_write(0x0, 0x38);
   lcd_write(0x0, 0x08);
   lcd_write(0x0, 0x01);
   wait(5000);
   lcd_write(0x0, 0x06);	
   lcd_write(0x0, 0x0C);
   lcd_write(0x0, 0x80);
}

void lcd_backlight_controller(uint16 ks, uint8* lkey_state_up, uint8* lkey_state_down, uint8* last_lcd){															
   uint8 nkey_state_up   = ((uint8) ks);
   uint8 nkey_state_down = ((uint8) (ks>>8));
   if( nkey_state_up != *lkey_state_up || nkey_state_down != *lkey_state_down ){
      lcd_on_until = timer_count+10000;
   }
   *lkey_state_up   = nkey_state_up;
   *lkey_state_down = nkey_state_down;
	 if( lcd_on_until > timer_count )
		 lcd_backlight(1);
	 else
		 lcd_backlight(0);
				
}

/*void lcd_backlight_controller(uint16 ks, uint8* lkey_state_up, uint8* lkey_state_down, uint8* last_lcd){															
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
				
}*/

void lcd_backlight (uint8 state) {
   DP7   = 0x00F0;
   P7_P4 = state;
}

void lcd_write(uint8 data_type, uint8 data_byte){
   DP7_P6= 0x1;
   P7_P6 = 0x0;
   DP7_P5= 0x1;
   P7_P5 = 0x1;
   DP7_P7= 0x1;
   P7_P7 = data_type;
   IC3 	= data_byte;
   wait(20);
   P7_P5 = 0x0;
   wait(20);
}

void lcd_setline(uint8 line) {
   switch(line) {
      case 0: lcd_write(0x0, 0x80); break;
      case 1: lcd_write(0x0, 0xC0); break;
      case 2: lcd_write(0x0, 0x94); break;
      case 3: lcd_write(0x0, 0xD4); break;
      default: break;
   }
}

void lcd_sendstring(uint8 line,  char* str) {
   uint8 i = 0;
   uint32 count = 20;
   lcd_setline(line);
   while(i<21 && str[i] != '\0') {
      lcd_write(0x1, str[i]);
      count--;
      i++;
   }
   while(count>0){
      lcd_write(0x1, 0x20); //0x20 = ASCII SPACE
      count--;
   }
				
}

void lcd_writestatus(uint32 cycle, uint16 temp){
   char message[21];
   
   sprintf (message, "Temp: %d", temp);
   lcd_sendstring(0, message);
   
   sprintf (message, "Freq: %ld", cycle);
   lcd_sendstring(1, message);
   
   if( (temp > MAX_TEMP || temp < MIN_TEMP) )
      sprintf (message, "WARNING: TEMP", 0x0);
   else
      sprintf (message, " ", 0x0);
   lcd_sendstring(2, message);
   
}

void wait(uint16 us) {
   uint32 t = T_WAIT * (uint32)us;
   uint32 i = 0;
   for(i=0; i<=t; i++);
}