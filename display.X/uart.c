#include "sys.h"

void initUART()
{
    // TXSTA REGISTER
    CSRC=0;    // 0: SLAVE MODE(clock from external source)
    TX9=0;     // Selects 8-bit transmission
    TXEN=1;    // Transmit enabled
    SYNC=0;    // Asynchronous mode
    BRGH=1;    // High Speed   BAUD = FOSC/(16(X+1))
    TRMT=1;    //
    TX9D=0;
    // RCSTA REGISTER
    SPEN=1;    // Serial port enabled
    RX9=0;     // Selects 8-bit transmission
    SREN=1;    // Single Recive Enable Bit
    CREN=1;    // Enables continuous receive
    ADDEN=0;   // Address Detect Enable bit
    FERR=0;    //
    OERR=0;    //
    RX9D=0;    //
    TRISC=0X80;// 
    SPBRG=0X05;// BAUD:115200 -> 11.0592MHZ
    
    // RCIE REGISTER
    RCIE = 1;   // Revice Interrupt On
    
    // INTERRUPT
    PEIE=1;     // Peripheral Interrupt Enable bit
}

/*************** Serial Port 1 Send One Byte ****************/
void UART_1SendOneByte(char c)
{
    TXREG = c;
    while(!TRMT);           //??????       
}

/************** Serial Port 1 Send String ****************/
void Uart_1SendStr(const char* data_at)
{
	while(*data_at)
	{
		UART_1SendOneByte(*data_at++);	
	}
}