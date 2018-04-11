#include "../sys.h"

void Digitron_Send_8bit(uchar dat)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        if(dat&0x01) {
            LED_DIO=1;
        }
        else{ LED_DIO=0;}
        LED_CLK=0;
        dat=dat>>1;
        LED_CLK=1;
    }
}

void Digitron_Command(uchar device,uchar com)
{
    LED_CS = LED_IGNORE;    // High level
    LED_CS = device;        // Low level
    delay_us(1);
    Digitron_Send_8bit(com);
}
