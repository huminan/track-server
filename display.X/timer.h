/* 
 * File:   timer.h
 * Author: 17221
 *
 * Created on 2018?1?11?, ??10:47
 */

#ifndef TIMER_H
#define	TIMER_H

// fosc: 11.0592MHZ
#define T0_11_0592_50_ONESEC   0x28 // T0 Every 50 times 1s

extern volatile unsigned char timer0_cnt;
extern volatile int sec_cnt;

void Init_Timer0();
void DelaySec(unsigned char sec);
void delay_us(unsigned char usec);

#endif	/* TIMER_H */

