#include "../sys.h"

uchar const CODE[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0xef,0x6f}; // led com-lunar code

queue_array digitron1, digitron2, digitron3;



// Initialize former n Digitrons '0'
void Init_Digitrons()
{
    queueArray_init(&digitron1);
    queueArray_init(&digitron2);
    queueArray_init(&digitron3);
    
    Digitron_Display(&digitron1);
    Digitron_Display(&digitron2);
    Digitron_Display(&digitron3);
}

// TM1616 display 4 bit digitrons
void Digitron_Display(queue_array *que)
{
    uchar fro = que->front;
    for(uchar i=0; i<3; i++)
    {
        if(fro+i == LOCATION_MAX)
            fro = 0;
        else
            fro = fro+i;
        
        Digitron_Command(i, 0x00); // Configure display Mode, 4 bit 7 section
        Digitron_Command(i, 0x40); // Configure data Command, Write data into Display Register
        Digitron_Command(i, 0xc0); // Configure display address, Start from 00H
        for(uchar j=0;j<4;j++) //Send display data
        {
            uchar num = que->data[fro][j]-0x30;
            if(num>10)
            {
                // Error!
                num = 9;
            }
            Digitron_Send_8bit(CODE[num]); //
            Digitron_Send_8bit(0);    //

        }
        Digitron_Send_8bit(0x8F);    // Display control mode, Open display and light level: 8
        LED_CS = LED_IGNORE;    // High level
    }
}

void Digitron_Update()
{
    char order_num[4], rider;
    for(uchar i=0;i<4;i++)
        order_num[i]=arr_rcv_section1[i];
    rider = arr_rcv_section2[0];
    
    
    
    switch(rider)
    {
        case '1':
        {
            queueArray_in(&digitron1, order_num);
            Digitron_Display(&digitron1);
        }
        case '2':
        {
            queueArray_in(&digitron2, order_num);
            Digitron_Display(&digitron2);
        }
        case '3':
        {
            queueArray_in(&digitron3, order_num);
            Digitron_Display(&digitron3);
        }
    }
}