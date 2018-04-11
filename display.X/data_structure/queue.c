#include "../sys.h"

uchar first_time=1;

void queueArray_init(queue_array *Q)
{
    Q->front = 0;
    Q->rear = 0;
    for(uchar i=0; i<LOCATION_MAX; i++)
        for(uchar j=0; j<DATA_MAXSIZE; j++)
            Q->data[i][j] = 0;
}

void queueArray_in(queue_array *Q, char *buf)
{
    for(uchar i=0; i<DATA_MAXSIZE; i++)
    {
        Q->data[Q->rear][i] = buf[i];
    }
    
    if(first_time)
    {
        Q->rear++;
        first_time = 0;
    }
    else if(Q->rear == Q->front)
    {
        if(Q->rear == LOCATION_MAX-1)
        {
            Q->rear = 0;
            Q->front = 0;
        }
        else
        {
            Q->rear++;
            Q->front++;
        }
    }
    else
    {
        if(Q->rear == LOCATION_MAX-1)
            Q->rear = 0;
        else
            Q->rear++;
    }
}