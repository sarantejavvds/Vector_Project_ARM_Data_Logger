#include <lpc214x.h>
#include "delay.h"
#include "defines.h"
#include "lcd.h"
#include "dht11.h"
#include "uart0.h"
#include "kpm.h"
//#include "uart_declarations.h"
#include "interrupt.h"
/*
#define FOSC      12000000

#define CCLK  	  5*FOSC

#define PCLK  	  CCLK/4

#define PREINT_VAL ((PCLK/32768)-1)

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768)) */

int main (void)
{
	unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;

	Init_UART0();  
	LCD_Init();
	rtc_init();
	InitKPM();
	
	PREINT=PREINT_VAL;

  PREFRAC=PREFRAC_VAL;

  CCR=0x01;
	
  Write_str_LCD("Data logger"); 
	delay_ms(5000);
  Write_CMD_LCD(0x01);

	while(1)
	{	   
	 UART_rtc();
	 rtc_LCD();
	 Enable_EINT0();	

		dht11_request();
		dht11_response();
		humidity_integer = dht11_data();
		humidity_decimal = dht11_data();
		temp_integer = dht11_data();
		temp_decimal = dht11_data();
		checksum = dht11_data();

		if((humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )
		{
			Write_str_LCD("Checksum Error\r\n");
		}
		else
		{
			Write_CMD_LCD(0x80);
			Write_str_LCD("H : ");
			Write_int_LCD(humidity_integer);
			Write_DAT_LCD('.');
			Write_int_LCD(humidity_decimal);
			Write_str_LCD(" % RH ");
			Write_CMD_LCD(0xC0);
			Write_str_LCD("T : ");
			Write_int_LCD(temp_integer);
			Write_DAT_LCD('.');
			Write_int_LCD(temp_decimal);
			Write_int_LCD(223);
			Write_str_LCD("C");
			delay_ms(1000);
			Write_CMD_LCD(0x01);
			Write_CMD_LCD(0x80);
			Write_str_LCD("Checksum : ");
			Write_int_LCD(checksum);

			//delay_ms(100);
	//Write_CMD_LCD(0x01); 
			//UART_rtc();

			UART0_Tx_str("H : ");
		  UART0_Tx_int(humidity_integer);
			UART0_Tx_char('.');
			UART0_Tx_int(humidity_decimal);
			UART0_Tx_str(" % RH ");
			UART0_Tx_str("T : ");
		  UART0_Tx_int(temp_integer);
			UART0_Tx_char('.');
			UART0_Tx_int(temp_decimal);
			UART0_Tx_int(223);
			UART0_Tx_str("C");
			UART0_Tx_str("Checksum : ");
			UART0_Tx_int(checksum);
			UART0_Tx_str("\r\n");
			delay_ms(1000);
			
		}

	}

}
