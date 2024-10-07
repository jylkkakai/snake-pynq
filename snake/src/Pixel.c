#include "Pixel.h"

// Set value of one pixel at led matrix
void SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {

  // Set new pixel value. Put values to dots array at correct places
  uint16_t *coord = 0x41220000;
  uint32_t *data = 0x41210000;

  *coord = x | y << 8;
  *data = b | g << 8 | r << 16;
}

void set_matrix(Snake *snake, Coordinate *food) {

  // Clear matrix. Set all pixels to zero
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      SetPixel(i, j, 0, 0, 0);
    }
  }

  SetPixel(food->x, food->y, 255, 0, 0);
  for (int i = 0; i < snake->length; i++) {
    SetPixel(snake->coordinates[i].x, snake->coordinates[i].y, 255, 255, 255);
  }
}
