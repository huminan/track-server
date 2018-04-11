/* 
 * File:   main.c
 * Author: 17221
 *
 * Created on 2018/1/10/, 9:11
 */
#include "sys.h"


__CONFIG(0x3B32);
/* Need receive from local and send it to storage
 * 
 */
void main()
{
    TRISA = 0x00;
    TRISB = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;
    PORTA = 0x00;
    Init_Digitrons();   // Initialize former n Digitrons '0'
    initUART();          // Initiallize Serial Port
    Init_Timer0();       // Initiallize Timer0
    Interrupt_Gross(1);      // Open Gross Interrupt
    
    DelaySec(3);    // Wait for Wifi Start
    CleanWifiRcv();

// Start detect
    if(!Send_ATComm("AT\r\n", "OK", 7, WAIT))  // If Failed
    {
        PORTA=0x01;
        while(1);
    }
    
    // The first time boot
    
    Send_ATComm("ATE0\r\n", "OK", 1, WAIT);
    
    if(!Send_ATComm("AT+CWMODE=1\r\n", "OK", 1, NO_WAIT))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }
    Send_ATComm("AT+RST\r\n", "OK", 1, NO_WAIT);
    DelaySec(3);
    
// Allow Muti Connection
    if(!Send_ATComm("AT+CIPMUX=1\r\n", "OK", 3, NO_WAIT))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }
    
    
// Connect to Router
    if(!Send_ATComm(ROUTER_SSID, "OK", 10, NO_WAIT))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }

// Check up IP address
/*    if(!Send_ATComm("AT+CIFSR\r\n", STATIC_IP, 3, NO_WAIT))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }
 * */
 Uart_1SendStr("AT+CIFSR\r\n");
 DelaySec(1);
 CleanWifiRcv();
    
// Configuer As Server, Port num is 1592
    if(!Send_ATComm("AT+CIPSERVER=1,1592\r\n", "OK", 3, NO_WAIT))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }
    
// Configure Transparent Mode: Server and Mux can't build Transparent mode...
    /*
    if(!(Send_ATComm("AT+CIPMODE=1\r\n", "Link is builded", 1, NO_WAIT)|!Send_ATComm("AT+CIPMODE=1\r\n", "OK", 1, NO_WAIT)))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }
    */
    
// Configure Server Overtime, 5 min overtime
    if(!Send_ATComm("AT+CIPSTO=300\r\n", "OK", 3, NO_WAIT))
    {
        // Failed
        PORTA=0x01;
        while(1);
    }

    
// Configuration success, Start to recive
    config_ok = 1;
    
    while(1);
}


