#include <LPC21xx.h>
#include "types.h"

#include "defines.h"

#include "kpmdefines.h"

u8 kpmLUT[4][4] =
                  {
                   {'1','2','3','A'},
                   {'4','5','6','B'},
                   {'7','8','9','C'},
                   {'*','0','#','D'}
                  };
									
//#define OPINs_8 8

void InitKPM(void)
{
 SETBIT(IODIR1,ROW0);
 SETBIT(IODIR1,ROW1); 
 SETBIT(IODIR1,ROW2);
 SETBIT(IODIR1,ROW3);
}

u8 ColScan(void)
{
 u32 t1,t2,t3,t4;

 t1=READBIT(IOPIN1,COL0);
 t2=READBIT(IOPIN1,COL1);
 t3=READBIT(IOPIN1,COL2);
 t4=READBIT(IOPIN1,COL3);

	return (t1&t2&t3&t4);
}

u8 Rowcheck()
{
 u8 rNo;

 SCLRBIT(IOCLR1,ROW0);
 SSETBIT(IOSET1,ROW1);
 SSETBIT(IOSET1,ROW2);
 SSETBIT(IOSET1,ROW3);

	if(!ColScan())
 {
  rNo=0;
  goto last;
 }

 SSETBIT(IOSET1,ROW0);
 SCLRBIT(IOCLR1,ROW1);
 SSETBIT(IOSET1,ROW2);
 SSETBIT(IOSET1,ROW3);

 if(!ColScan())
 {
 rNo=1;
 goto last;
 }

 SSETBIT(IOSET1,ROW0);
 SSETBIT(IOSET1,ROW1);
 SCLRBIT(IOCLR1,ROW2);
 SSETBIT(IOSET1,ROW3);

 if(!ColScan())
 {
  rNo=2;
  goto last;
 }

 SSETBIT(IOSET1,ROW0);
 SSETBIT(IOSET1,ROW1);
 SSETBIT(IOSET1,ROW2);
 SCLRBIT(IOCLR1,ROW3);
 
 if(!ColScan())
 {
  rNo=3;
 }

 last:
      SCLRBIT(IOCLR1,ROW0);
      SCLRBIT(IOCLR1,ROW1);
      SCLRBIT(IOCLR1,ROW2);
      SCLRBIT(IOCLR1,ROW3);
 
 return rNo;
}

u8 Colcheck()
{
 u8 cNo;
	
if(READBIT(IOPIN1,COL0) == 0)
{
 cNo=0;
}
else if(READBIT(IOPIN1,COL1) == 0)
{
 cNo=1;
}
else if(READBIT(IOPIN1,COL2) == 0)
{
 cNo=2;
}
else if(READBIT(IOPIN1,COL3)==0)
{
 cNo=3;
}

 return cNo;
}

u8 keyscan()
{
 u8 rNo,cNo,KeyV;
	
 while(ColScan());

 rNo=Rowcheck();

 cNo=Colcheck();

 KeyV=kpmLUT[rNo][cNo];

 return KeyV;
}
