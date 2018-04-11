/* 
 * File:   wifi.h
 * Author: 17221
 *
 * Created on 2018?1?11?, ??10:27
 */

#ifndef WIFI_H
#define	WIFI_H

#define MAXRCV  50
#define AT_SEND_MAX 3   // Send AT Command 3 times At Most

#define ROUTER_SSID "AT+CWJAP=\"deet\",\"172210086\"\r\n"
#define ROUTER_SSID2 "AT+CWJAP=\"DELIXI\"\r\n"
#define STATIC_IP   "192.168.1.5"

#define NO_WAIT 0
#define WAIT    1

extern char rcv_wifi[MAXRCV];
extern unsigned char WifiRcvCnt;

void CleanWifiRcv(void);
bit Match(const unsigned char *a);
char Send_ATComm(const char *comm, const char *ret, unsigned char delay, char wait);

char * mid(char *dst,char *src, int n,int m);
char Locate_Pos(char *buf,char cx);
char Locate_Colon(char *buf,char cx);
//char Get_DataId();
char Get_GpsDataLen();
void Analyze_GpsData(char* rider, double *lati, double *longi);


#endif	/* WIFI_H */

