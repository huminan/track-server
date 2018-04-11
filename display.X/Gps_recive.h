/* 
 * File:   Gps_recive.h
 * Author: 17221
 *
 * Created on 2018?1?12?, ??2:40
 */

#ifndef GPS_RECIVE_H
#define	GPS_RECIVE_H

#define LATITUDE 10
#define LONGITUDE 10


#define DST_LATI    500      //2839.00500
#define DST_LONGI   89100    //11552.89100
// SRC_LATI = 6500
// SRC_LONGI = 29600

#define DST_PER_6   6823

extern unsigned char pos;
extern int distance;
extern char val_rcv_len;
extern long val_rcv_lati, val_rcv_longi;
extern char arr_rcv_len[3], arr_rcv_who[2], arr_rcv_section1[LATITUDE], arr_rcv_section2[LONGITUDE];
extern unsigned char LenRcvCnt, WhoRcvCnt, LatiRcvCnt, LongiRcvCnt;


extern unsigned char config_ok;

void Pos_meet(unsigned char pos);
void CleanGpsRcv(void);
unsigned char Calc_DistanceLevel();
void Distance_Update();

#endif	/* GPS_RECIVE_H */

