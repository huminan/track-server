#include "sys.h"


void interrupt SerialService(void) 
{  
    char tmp;
    if(RCIE&&RCIF)  // Serial Recive
    {  
        // Not Shut Interrupt up...
        
        RCIF=0;       // Clear Recive Flag
        tmp=RCREG;    // Recive Data  
        rcv_wifi[WifiRcvCnt] = tmp;
        WifiRcvCnt++;
        
        if(WifiRcvCnt > MAXRCV)
		{
			WifiRcvCnt = 0;
		}
        
        if(config_ok)
        {
            if(tmp == '+')  // Another new information arrive
            {
                // clean all
                pos = 0;
            }
            if((tmp == ',')||(tmp ==':'))
            {
                pos++;
                Pos_meet(pos);  // some analysis need to be done
            }
            else
            {
                switch(pos)
                {
                    case 1: 
                    {
                        break;
                    }
                    case 2:
                    {
                        arr_rcv_len[LenRcvCnt++] = tmp;    // Record recived info's length
                        break;
                    }
                    case 3:
                    {
                        arr_rcv_who[WhoRcvCnt++] = tmp;        // Record Who send the Massage
                        break;
                    }
                    case 4:
                    {
                        arr_rcv_section1[LatiRcvCnt++] = tmp;
                        break;
                    }
                    case 5:
                    {
                        arr_rcv_section2[LongiRcvCnt++] = tmp;
                        if(WifiRcvCnt == val_rcv_len)   // recive done
                        {
                            pos++;
                            Pos_meet(pos);
                        }
                        break;
                    }
                    
                }
            }
        }   
    }
    
    if(T0IF == 1)   // Timer0 Interrupt
    {
        T0IF = 0;
        TMR0 = T0_11_0592_50_ONESEC;
        if(timer0_cnt++ > 50)
        {
        timer0_cnt = 0;
		sec_cnt++;
        }
    }
}



/*************?????**************/
void Interrupt_Gross(uchar mov)
{
    if(mov)
        GIE = 1;
}