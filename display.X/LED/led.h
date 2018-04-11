/* 
 * File:   led.h
 * Author: 17221
 *
 * Created on 2018?1?12?, ??3:05
 */

#ifndef LED_H
#define	LED_H

extern queue_array digitron1;
extern queue_array digitron2;
extern queue_array digitron3;

void Init_Digitrons();
void Digitron_Display(queue_array *que);
void Digitron_Update();

#endif	/* LED_H */

