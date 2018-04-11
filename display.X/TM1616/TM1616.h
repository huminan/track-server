/* 
 * File:   TM1616.h
 * Author: 17221
 *
 * Created on 2018?1?12?, ??11:50
 */

#ifndef TM1616_H
#define	TM1616_H

#define LED_DIO     RC3
#define LED_CLK     RC2
// CS: 4-16 yimaqi PORTD low 4 bit
#define LED_CS      PORTD

#define LED_IGNORE  0xF0        // Set all chips' CS high

void Digitron_Send_8bit(unsigned char data);
void Digitron_Command(unsigned char device,unsigned char com);

#endif	/* TM1616_H */

