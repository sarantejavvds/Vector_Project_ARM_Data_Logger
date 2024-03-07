#include "types.h"

void Write_CMD_LCD(u8);

void Write_DAT_LCD(u8);

void Write_LCD(u8);

void LCD_Init(void);

void Write_str_LCD(u8 *);

void Write_int_LCD(s32);//signed int(2 byte)-> -32768 to 32767

void Write_float_LCD(f32 , u8 );
