#include<lpc21xx.h>
#include"delay.h"
#include"defines.h"
#include"lcd.h"
#include"types.h"

void rtc_Init(void)
{
 CCR=0x02;
HOUR=10;
MIN=50;
SEC=22;
DOM=3;
MONTH=1;
YEAR=2024;
}




