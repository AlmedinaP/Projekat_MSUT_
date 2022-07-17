#ifndef __USART2_H_
#define __USART2_H_

#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx.h"
#include "misc.h"

#define USART2_BAUDRATE_115200		0x0000016C
#define USART2_BAUDRATE_9600		0x00001117
#define USART1_BAUDRATE_115200		0x000002D9
#define USART2_BAUDRATE_460800		0x0000005B

void initUSART2(uint32_t baudrate);
void putcharUSART2(uint8_t data);
void printUSART2(char * str, ... );
void sprintUSART2(uint8_t * str);

uint8_t getcharUSART2();

void enIrqUSART2(void);
#endif 
