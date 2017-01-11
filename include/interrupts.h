#ifndef __ECE353_INTERRUPTS_H__
#define __ECE353_INTERRUPTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "TM4C123.h"

#include "uart.h"
#include "pc_buffer.h"
#include "gpioPort.h"
#include "lcd.h"

void UART0_Handler(void);
void WDT0_Handler(void);
void TIMER0A_Handler(void);
void GPIOD_Handler(void);
void SysTick_Handler(void);

#endif
