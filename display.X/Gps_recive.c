#include "sys.h"

unsigned int gps_location;

unsigned char pos = 0;
char val_rcv_len;
long val_rcv_lati, val_rcv_longi;
char arr_rcv_len[3], arr_rcv_who[2], arr_rcv_section1[LATITUDE], arr_rcv_section2[LONGITUDE];
uchar LenRcvCnt, WhoRcvCnt, LatiRcvCnt, LongiRcvCnt;

uchar config_ok = 0; // Initiallization done. Start working.

void Pos_meet(uchar pos)
{
    switch(pos)
    {
        case 3:     // Get data's length
        {
            WifiRcvCnt = 0;
            val_rcv_len = atoi(arr_rcv_len);
            break;
        }
        case 4:     // Get Who Send the Message:'A':rider ; 'B':storage ; 'C':local
        {
            break;
        }
        
        case 5:
        {
            break;
        }
        case 6: // recive done
        {
            switch(arr_rcv_who[0])
            {
                case 'A':   // Message from Rider 
                {
                    char arr_rcv_lati[6], arr_rcv_longi[6];
                    
                    // only get decimal of the lati/longi, discard integer
                    for(char i = 0; i<LATITUDE; i++)
                    {
                        if(arr_rcv_section1[i]=='.')
                        {
                            for(char j = 0; j<LATITUDE; j++)
                            {
                                arr_rcv_lati[j] = arr_rcv_section1[i+j+1];
                            }
                            break;
                        }
                    }
                    for(char i = 0; i<LONGITUDE; i++)
                    {
                        if(arr_rcv_section2[i]=='.')
                        {
                            for(char j = 0; j<LONGITUDE; j++)
                            {
                                arr_rcv_longi[j] = arr_rcv_section2[i+j+1];
                            }
                            break;
                        }
                    }
                    
                    val_rcv_lati = atol(arr_rcv_lati);
                    val_rcv_longi = atol(arr_rcv_longi);
                    
                    // Because only pick decimal up, longitude sometimes 1.00000 bigger
                    if(val_rcv_longi-30000 < 0)
                        val_rcv_longi+=100000;
                    
                    Distance_Update();
                    break;
                }
                case 'B':   // Message from Storage
                {
                    Digitron_Update();
                    break;
                }
                case 'C':   // Message from Local
                {
                    break;
                }
            }
            CleanGpsRcv();
        }
    }
}

void CleanGpsRcv(void)
{
	uchar i = 0;
	for(i=0; i<=LATITUDE; i++)
	{
		arr_rcv_section1[i] = 0;	
	}
    for(i=0; i<=LONGITUDE; i++)
	{
		arr_rcv_section2[i] = 0;	
	}
    for(i=0; i<=2; i++)
	{
		arr_rcv_len[i] = 0;	
	}
    for(i=0; i<=2; i++)
	{
		arr_rcv_who[i] = 0;	
	}
	LatiRcvCnt = 0;	
    LongiRcvCnt = 0;	
    LenRcvCnt = 0;	
    WhoRcvCnt = 0;
}

// Return How Far : by 1~6 level
uchar Calc_DistanceLevel()
{
    uchar level;
    unsigned int t;
    t = (unsigned int)sqrt(pow(val_rcv_longi - DST_LONGI, 2)+pow(val_rcv_lati-DST_LATI, 2));
    level = (uchar)(t/DST_PER_6);
    return level;
}

void Distance_Update()
{
    uchar level;
    
    level = Calc_DistanceLevel();
    level--;    // For Calculate
    switch(arr_rcv_who[1])
    {
        case '1':
        {
            unsigned int dat;
            unsigned int mask = 0x07FF;
            dat = 0xF800<<level;
            mask |= dat;                // mask    <dat> <dat>111 1111 1111
            
            gps_location |= 0xF800;      // display 1111 1<dat> <dat> <dat>
            gps_location &= mask;
            
            Register_SendData(gps_location, 16);
        }
        case '2':
        {
            unsigned int dat;
            unsigned int mask = 0xF83F;
            dat = 0xF800<<level;
            dat = dat >> 5;
            mask |= dat;                // mask    1111 1<dat> <dat>11 1111
            
            gps_location |= 0x07C0;      // display <dat> <dat>111 11<dat> <dat>
            gps_location &= mask;
            
            Register_SendData(gps_location, 16);
        }
        case '3':
        {
            unsigned int dat;
            unsigned int mask = 0xFFC1;
            dat = 0xF800<<level;
            dat = dat >> 10;
            mask |= dat;                 // mask    1111 1111 11<dat> <dat>1
            
            gps_location |= 0x003E;      // display <dat> <dat> <dat>11 111<dat>
            gps_location &= mask;
            
            Register_SendData(gps_location, 16);
        }
        // No Problem of Initialization.
    }
}