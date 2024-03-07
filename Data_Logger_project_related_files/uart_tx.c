#include<LPC214x.h>

#include "uart0.h"

#include "delay.h"

#include "lcd.h"

/*#define FOSC      12000000

#define CCLK  	  5*FOSC

#define PCLK  	  CCLK/4

#define PREINT_VAL ((PCLK/32768)-1)

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768)) */


//enum weak{sun,mon,tue,wed,thur,fri,sat};
//enum weak day;
  
void UART_rtc()
{ 
	UART0_Tx_char((HOUR/10)+'0');
  UART0_Tx_char((HOUR%10)+'0');
  UART0_Tx_char(':');
  UART0_Tx_char((MIN/10)+'0');
  UART0_Tx_char((MIN%10)+'0');
  UART0_Tx_char(':');
  UART0_Tx_char((SEC/10)+'0');
  UART0_Tx_char((SEC%10)+'0');
	UART0_Tx_str(" ");
    //UART0_Tx_str("\r\n");
	UART0_Tx_char((DOM/10)+'0');
  UART0_Tx_char((DOM%10)+'0');
  UART0_Tx_char('/');
  UART0_Tx_char((MONTH/10)+'0');
  UART0_Tx_char((MONTH%10)+'0');
  UART0_Tx_char('/');
  UART0_Tx_char((YEAR/10)+'0');
  UART0_Tx_char((YEAR%10)+'0');
	UART0_Tx_str(" ");
	//UART0_Tx_char(day);
	//UART0_Tx_char(DOW);
    UART0_Tx_str("\r\n");
		//delay_ms(1000);
}

void rtc_LCD()
{
	Write_CMD_LCD(0xc0);
	Write_DAT_LCD((HOUR/10)+48);
	Write_DAT_LCD((HOUR%10)+48);
	Write_DAT_LCD(':');
	Write_DAT_LCD((MIN/10)+48);
	Write_DAT_LCD((MIN%10)+48);
	Write_DAT_LCD(':');
	Write_DAT_LCD((SEC/10)+48);
	Write_DAT_LCD((SEC%10)+48);
	Write_DAT_LCD(' ');
	Write_CMD_LCD(0x80);
	Write_DAT_LCD((DOM/10)+48);
	Write_DAT_LCD((DOM%10)+48);
	Write_DAT_LCD('/');
	Write_DAT_LCD((MONTH/10)+48);
	Write_DAT_LCD((MONTH%10)+48);
	Write_DAT_LCD('/');
	Write_DAT_LCD(YEAR/10+48);
	Write_DAT_LCD((YEAR%10)+48);
	delay_ms(1000);
}	


void rtc_init()
{
  SEC=20; 
  MIN=00; 
  HOUR=8;
  DOM=19;
  MONTH=1;
  YEAR=24;
  //day=enum weak(0);

}
