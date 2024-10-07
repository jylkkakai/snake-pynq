#ifndef PIXEL_H_
#define PIXEL_H_
#include "../../snake_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xgpiops.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xscugic.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xttcps.h"
#include "platform.h"
#include "snake.h"
#include <stdint.h>

void setup();
void SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
void set_matrix(Snake *snake, Coordinate *food);
#endif /* PIXEL_H_ */
