/* 
 * File:   main.c
 * Author: 17221
 *
 * Created on 2018/1/6 21:08
 */
#include <pic.h>
#include <stdio.h>
#include <stdlib.h>

#define uint_8 unsigned char
#define uint_16 unsigned int

__CONFIG(0x3B31);

uint_8 data_rcv;

/*
 * 
 */
void UART_Init()
{
    TRISC |= (1<<7);    // data direction
    TRISC &= (~(1<<6));
    SPBRG=0X4D;         //12MHZ foc 9600BD
	TXSTA=0X24;     
	RCSTA=0X80;
	CREN=1;		
	SYNC=0;		
	SPEN=1;		
	RCIE=1; 	
	PEIE=1;		
	GIE=1;		
}

/*
 * 
 */
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

void interrupt connect()
{
    if(RCIF==1)
    {
        TXREG = "AT+WHAT";
        data_rcv = RCREG;
    }
}