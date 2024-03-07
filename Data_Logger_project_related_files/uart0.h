#ifndef _UART0_H_

#define _UART0_H_


void Init_UART0(void);

void UART0_Tx_char(unsigned char);

unsigned char UART0_Rx_char(void);

void UART0_Tx_str(char *);

void UART0_Tx_int(signed int);

void UART0_Tx_float(float,char);

void rtc_init(void);

void UART_rtc(void);

void rtc_LCD(void);

#define FOSC      12000000

#define CCLK  	  5*FOSC

#define PCLK  	  CCLK/4

#define PREINT_VAL ((PCLK/32768)-1)

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))

#endif
