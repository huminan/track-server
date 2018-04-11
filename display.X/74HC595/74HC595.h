/* 
 * File:   74HC595.h
 * Author: 17221
 *
 * Created on 2018?1?12?, ??11:53
 */

#ifndef HC595_H
#define	HC595_H

#define CLK     RE0     // flow up: move
#define SI      RE1     // data
#define RCK     RE2     // flow up: output

void Register_SendData(unsigned int dat, unsigned char length);

#endif

