#define FOSC 12000000
#define CCLK 5*FOSC
#define PCLK CCLK/4
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))

#define WORD_LEN_8 3
#define DLAB_BIT 7
#define DR_BIT 0
#define THRE_BIT 5
#define TEMT_BIT 6

//#define FUN2 1 
