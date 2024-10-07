
#include "weights.h"

// Fully connected neural network layer
void dense(float (*out)[], float (*input)[], float (*weights)[],
           float (*biases)[], int w, int h) {

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {

      (*out)[i] += (*input)[j] * (*weights)[i + j * w];
    }
    (*out)[i] += (*biases)[i];
  }
}
// ReLU activation
void relu(float (*input)[], int len) {

  for (int i = 0; i < len; i++) {
    (*input)[i] = (*input)[i] > 0 ? (*input)[i] : 0;
  }
}

int get_action(float (*input)[]) {
  // float input[] = {5, 6, 2, 1, 1, 3, 100, 100, 100 ,1, 100, 100};
  // float (*in_ptr)[] = &input;
  float layer_0_out[24] = {0};
  float layer_1_out[24] = {0};
  float layer_2_out[4] = {0};
  float(*layer_0_w_ptr)[] = &layer_0_w;
  float(*layer_0_b_ptr)[] = &layer_0_b;
  float(*layer_1_w_ptr)[] = &layer_1_w;
  float(*layer_1_b_ptr)[] = &layer_1_b;
  float(*layer_2_w_ptr)[] = &layer_2_w;
  float(*layer_2_b_ptr)[] = &layer_2_b;
  float(*layer_0_out_ptr)[] = &layer_0_out;
  float(*layer_1_out_ptr)[] = &layer_1_out;
  float(*layer_2_out_ptr)[] = &layer_2_out;

  dense(layer_0_out_ptr, input, layer_0_w_ptr, layer_0_b_ptr, 24, 12);
  relu(layer_0_out_ptr, 24);
  dense(layer_1_out_ptr, layer_0_out_ptr, layer_1_w_ptr, layer_1_b_ptr, 24, 24);
  relu(layer_1_out_ptr, 24);
  dense(layer_2_out_ptr, layer_1_out_ptr, layer_2_w_ptr, layer_2_b_ptr, 4, 24);
  relu(layer_2_out_ptr, 24);
  int action = 0;
  float temp = 0.0;
  for (int i = 0; i < 4; i++) {

    if (layer_2_out[i] > temp) {
      temp = layer_2_out[i];
      action = i;
    }
  }

  return action;
}
