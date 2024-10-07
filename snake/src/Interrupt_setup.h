#ifndef INTERRUPT_SETUP_H_
#define INTERRUPT_SETUP_H_
#include "../../snake_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xgpiops.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xscugic.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xttcps.h"
#include "platform.h"
#include <stdio.h>

int SetupGpioInterruptSystem();
int SetupTimerInt();
int SetupTimerInt1();
void ButtonHandler(void *CallBackRef, u32 Bank, u32 Status);
void TickHandler(void *CallBackRef);
void TickHandler1(void *CallBackRef);
void init_interrupts();
void change_freq(uint32_t freq);

#endif /* SRC_INTERRUPT_SETUP_H_ */
