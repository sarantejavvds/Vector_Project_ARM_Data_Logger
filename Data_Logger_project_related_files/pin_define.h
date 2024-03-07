#include <LPC21xx.h>

#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H
#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3
#define CFGPIN(WORD,PINNO,FUNC) WORD=(PINNO<16)?((WORD&~(0X03<<(PINNO*2)))|(FUNC<<(PINNO*2))):((WORD&~(0X03<<((PINNO-16)*2)))|(FUNC<<((PINNO-16)*2)))
#define TxD0_0_0 FUN2
#define RxD0_0_0 FUN2
#endif
