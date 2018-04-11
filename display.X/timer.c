#include "sys.h"

volatile uchar timer0_cnt = 0;
volatile int sec_cnt = 0;

/* Timer0 Initiallization
 * Into 50 times per second
 */
void Init_Timer0()
{
    //11.0592MHZ
    OPTION=0x07;     // TMR0----256 prescaler
    TMR0 = T0_11_0592_50_ONESEC;       // every 50 times 1s
    
    T0IE = 1;        // Timer0 Interrupt On
    return;
}

/**************Delay Second**************/
void DelaySec(unsigned char sec)
{
	sec_cnt = 0;
	while(sec_cnt < sec);
    return;
}

// 11.0592MHZ no use in general
void delay_us(unsigned char usec)
{
    for(uchar i = usec; i>0; i--)
        for(uchar j = 2; j>0; j--);
        return;
}