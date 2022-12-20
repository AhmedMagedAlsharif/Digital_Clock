/* 
 * File:   switch.h
 * Author: ahmed
 *
 * Created on December 20, 2022, 10:21 AM
 */

#ifndef SWITCH_H
#define	SWITCH_H

#include "gpio.h"

uint8_t UP_SW_Pressed ;
uint8_t SET_SW_Pressed;
uint8_t DOWN_SW_Pressed;

void SW_Init(void);
void SW_Update(void);

#endif	/* SWITCH_H */

