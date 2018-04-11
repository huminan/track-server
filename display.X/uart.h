/* 
 * File:   uart.h
 * Author: 17221
 *
 * Created on 2018?1?10?, ??9:25
 */

#ifndef UART_H
#define	UART_H

void initUART();
void UART_1SendOneByte(char c);
void Uart_1SendStr(const char* data_at);

#endif	/* UART_H */

