#include <LPC214x.h>

#include "delay.h"

#include "lcd.h"

#include "defines.h"

#include "types.h"


#define LCD_DAT 16

#define RS 11

#define RW 19

#define EN 12

void LCD_Init(void)
{
		WRITEBYTE(IODIR0,LCD_DAT,0xFF);

		WRITEBIT(IODIR0,RS,1);

		WRITEBIT(IODIR0,RW,1);

		WRITEBIT(IODIR0,EN,1);

		delay_ms(16);

    Write_CMD_LCD(0x30);

    delay_ms(6);

		Write_CMD_LCD(0x30);

    delay_ms(1);

    Write_CMD_LCD(0x30);

    delay_ms(1);

    Write_CMD_LCD(0x38);//set 8-bit mode of operation with 2 lines and 5X7 character font 

		Write_CMD_LCD(0x0F);//Turning OFF the display

		Write_CMD_LCD(0x01);//clearing the display

    Write_CMD_LCD(0x06);//Shifting the cursor to the right side after writing each byte onto the display

	//	Write_CMD_LCD(0x0f);//Enabling the display with blinking cursor
}

void Write_CMD_LCD(u8 cmd)
{
  WRITEBIT(IOCLR0,RS,1);

	Write_LCD(cmd);
}

void Write_DAT_LCD(u8 dat)
{
	WRITEBIT(IOSET0,RS,1);

	Write_LCD(dat);
}

void Write_LCD(u8 ch)
{

	WRITEBIT(IOCLR0,RW,1);

	WRITEBYTE(IOPIN0,LCD_DAT,ch);

	WRITEBIT(IOSET0,EN,1);

		delay_us(1);

	WRITEBIT(IOCLR0,EN,1);

	delay_ms(2);

}

void Write_str_LCD(u8 *p)
{

	while(*p)
  {
		Write_DAT_LCD(*p++);	
	}
}

void Write_int_LCD(s32 n)
{

	char a[10],i=0;

    if(n < 0)
    {

		 Write_DAT_LCD('-');

		 n=-n;

	  }

	do                       
	{
		a[i++] = n % 10 +48;	

		n = n / 10;

	}while(n);

  for( ; i>0 ; i--)
  {
		Write_DAT_LCD(a[i-1]);
	}

}

/*  main()
  {
  	  LCD_Init();
	  Write_DAT_LCD('A');
	  Write_CMD_LCD(0xc0);
	   Write_str_LCD("data logger");                            
	  while(1);
	  }	*/
