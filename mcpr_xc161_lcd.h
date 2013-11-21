#ifndef _LCD_H_
#define _LCD_H_

#include <XC161.h>
#include "Platform_types.h"

#define IC2 (*((uint8*) 0x100002))
#define IC3 (*((uint8*) 0x100004))

#define T_WAIT 6
#define MIN_TEMP 18
#define MAX_TEMP 25

void lcd_init();

void lcd_backlight (uint8 state);
void lcd_backlight_controller( uint16 ks, uint8* lkey_state_up, uint8* lkey_state_down, uint8* last_lcd );

void lcd_write(uint8 data_type, uint8 data_byte);
void lcd_setline(uint8 line);
void lcd_sendstring(uint8 line, char* str);
void lcd_sendall();
void lcd_writestatus(uint16* cycle, uint16* temp);

void wait(uint16 ms);

#endif