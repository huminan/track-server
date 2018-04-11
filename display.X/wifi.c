#include "sys.h"

char rcv_wifi[MAXRCV];
uchar WifiRcvCnt = 0;

/************Wifi ?????????**************/
void CleanWifiRcv(void)
{
	uchar i = 0;
	for(i=0; i<=MAXRCV; i++)
	{
		rcv_wifi[i] = 0;	
	}

	WifiRcvCnt = 0;	
}

/************* Send AT Command ***************/
// Send command and match return strings
// Delay: how long to failed
// wait=1: Just wait for return Strings, don't send again
// return 1: Success
// return 0: Failed
char Send_ATComm(const char *comm, const char *ret, uchar delay, char wait)
{
    uchar i;
    for(i = 0;i<delay;i++)
    {
        if(wait)
            Uart_1SendStr(comm);    // wait=WAIT
        else
            if(i==0)                // wait=NO_WAIT 
               Uart_1SendStr(comm);  
        DelaySec(1);
        if(Match(ret)) //Match
        {
            CleanWifiRcv();
            return 1;
        }
    }
    CleanWifiRcv();
    return 0;
}

// Pick up string from String
char * mid(char *dst,char *src, int n,int m) /*n为长度，m为位置*/
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n = len-m;    /*从第m个到最后*/
    if(m<0) m=0;    /*从第一个开始*/
    if(m>len) return NULL;
    p += m;
    while(n--) *(q++) = *(p++);
    *(q++)='\0'; /*有必要吗？很有必要*/
    return dst;
}

// Locate ','
char Locate_Pos(char *buf,char cx)
{	 		    
	char *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;// If exist inlegal character, assert no pos, return 0xff
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}

// Locata ':'
char Locate_Colon(char *buf,char cx)
{	 		    
	char *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;// If exist inlegal character, assert no pos, return 0xff
		if(*buf==':')cx--;
		buf++;
	}
	return buf-p;	 
}

/*  char Get_DataId()
    {
        uchar pos1;
        pos1 = Locate_Pos(rcv_wifi, 1);
        return rcv_wifi[pos1+1];
    }*/


// "+IPD,<ID>,<LEN>:<data>"
char Get_GpsDataLen()
{
    // Get data length
    char len_arr[3];
    char len_val;
    uchar pos2, colon;
    pos2 = Locate_Pos(rcv_wifi, 2);
    colon = Locate_Pos(rcv_wifi, 3);
    mid(len_arr, rcv_wifi, colon-pos2-1, pos2);
    len_val = (char)atoi(len_arr);  // Transform String to int to char
    return len_val;
}

// "+IPD,<ID>,<LEN>:<data>"
void Analyze_GpsData(char* rider, double *lati, double *longi)
{
    char info[MAXRCV];
    char len;
    char la[LATITUDE], lo[LONGITUDE];
    uchar pos1,pos2,pos3,pos4,colon;
    
    len = Get_GpsDataLen();
    
    colon = Locate_Pos(rcv_wifi, 3);
    
// Get data...maybe wrong
    mid(info, rcv_wifi, len-colon-1, colon);
    
    pos1 = Locate_Pos(info, 1);
    pos2 = Locate_Pos(info, 2);
    pos3 = Locate_Pos(info, 3);
    pos4 = Locate_Pos(info, 4);
    
    *rider = info[pos1-2];
    mid(la, info, pos3-pos2-1, pos2);
    mid(lo, info, len-pos4-1, pos4);
    
    *lati = atof(la);
    *longi = atof(lo);
}


/****************???????????*******************/
bit Match(const unsigned char *a)
{ 
	if(strstr(rcv_wifi,a)!=NULL)
		return 1;
	else
		return 0;
}
