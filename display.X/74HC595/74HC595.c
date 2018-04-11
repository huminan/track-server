#include "../sys.h"

void Register_SendData(unsigned int dat, uchar length)
{
    for(uchar i = 0; i<length; i++)
    {
        if(dat&0x01)
            SI=1;
        else SI=0;
        CLK = 1;
        dat = dat >> 1;
        CLK = 0;
    }
    RCK = 1;
    RCK = 0;
}
