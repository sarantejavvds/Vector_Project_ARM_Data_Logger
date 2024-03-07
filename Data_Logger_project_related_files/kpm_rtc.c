#include<lpc21xx.h>
#include"delay.h"
#include"LCD_declarations.h"
#include"defines.h"
#include"kpmdefines.h"
#include"kpm.h"
void rtc_init(void);
#define SW 16

int main()
{
u32 keyv;
LCD_Init();
rtc_init();
InitKPM();
SETBIT(IODIR0,SW);
while(1)
{
if(READBIT(IOPIN0,SW)==0)
{
while(READBIT(IOPIN0,SW)==0);
Write_str_LCD("1.HOUR 2.MIN 3.SEC");
keyv=keyscan();
switch(keyv)
{
case 1: HOUR=keyscan();
		Write_DAT_LCD(HOUR/10);
		Write_DAT_LCD(HOUR%10);
		break;
case 2:MIN=keyscan();
		Write_DAT_LCD(MIN/10);
		Write_DAT_LCD(MIN%10);
		break;
case 3:SEC=keyscan();
		Write_DAT_LCD(SEC/10);
		Write_DAT_LCD(SEC%10);
		break;
}
Write_DAT_LCD((HOUR/10)+48);
Write_DAT_LCD((HOUR%10)+48);
Write_DAT_LCD(':');
Write_DAT_LCD((MIN/10)+48);
Write_DAT_LCD((MIN%10)+48);
Write_DAT_LCD(':');
Write_DAT_LCD((SEC/10)+48);
Write_DAT_LCD((SEC%10)+48);
Write_DAT_LCD(' ');
Write_DAT_LCD((DOM/10)+48);
Write_DAT_LCD((DOM%10)+48);
Write_DAT_LCD('/');
Write_DAT_LCD((MONTH/10)+48);
Write_DAT_LCD((MONTH%10)+48);
Write_DAT_LCD('/');
Write_DAT_LCD(YEAR/10+48);
Write_DAT_LCD((YEAR%10)+48);
delay_ms(1000);	
Write_CMD_LCD(0x01);
}
 }
 }

void rtc_init()
{
  SEC=20; //Initialized seconds
  MIN=00; //Initialized minutes
  HOUR=12;//Initialized hour
  DOM=03;
  MONTH=01;
  YEAR=24;
}




