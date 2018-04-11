/* 
 * File:   queue.h
 * Author: 17221
 *
 * Created on 2018?1?13?, ??1:23
 */

#ifndef QUEUE_H
#define	QUEUE_H

#define DATA_MAXSIZE    4
#define LOCATION_MAX    3

typedef struct{
    unsigned char rear;
    unsigned char front;
    char data[LOCATION_MAX][DATA_MAXSIZE];
}queue_array;

void queueArray_init(queue_array *Q);
void queueArray_in(queue_array *Q, char *buf);

#endif	/* QUEUE_H */

