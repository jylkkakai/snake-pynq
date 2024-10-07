
#include "../../snake_bsp/ps7_cortexa9_0/include/sleep.h"
// #include "../../snake_bsp/ps7_cortexa9_0/include/xgpiops.h"
// #include "../../snake_bsp/ps7_cortexa9_0/include/xil_printf.h"
// #include "../../snake_bsp/ps7_cortexa9_0/include/xparameters.h"
// #include "../../snake_bsp/ps7_cortexa9_0/include/xscugic.h"
#include "../../snake_bsp/ps7_cortexa9_0/include/xttcps.h"
#include "Interrupt_setup.h"
#include "Pixel.h"
#include "dnn.h"
#include "platform.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
// #include "weights.h"

#define leds *(uint8_t *)0x41200000
#define rgbs *(uint8_t *)0x41240000

// Comment this if you want to disable all interrupts
// #define enable_interrupts

int main() {

  init_platform();

  // #ifdef enable_interrupts
  //   init_interrupts();
  // #endif

  // Xil_ExceptionEnable();

  Snake snake;
  Snake *snake_ptr = &snake;
  Coordinate food;
  Coordinate *food_ptr = &food;
  int state[12] = {0};
  int(*state_ptr)[] = &state;
  srand(1);
  init_snake(snake_ptr, food_ptr, state_ptr);

  // Main loop
  while (1) {

    init_snake(snake_ptr, food_ptr, state_ptr);
    int end = 0;
    printf("New game\n");
    while (!end) {

      // Set led matrix
      set_matrix(snake_ptr, food_ptr);

      usleep(50000);

      // Get action from dnn
      snake_ptr->prev_action = snake_ptr->action;

      // Int to float
      float state_f[12] = {0};
      for (int i = 0; i < 12; i++) {
        state_f[i] = (float)(*state_ptr)[i];
      }
      snake_ptr->action = get_action(state_f);

      // Move snake per action
      end = move(snake_ptr, food_ptr, state_ptr);
    }
  }

  cleanup_platform();
  return 0;
}
