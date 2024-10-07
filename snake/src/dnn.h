#ifndef DNN
#define DNN

void dense(float *out, float *input, float *weights, float *biases, int w, int h);
void relu(float *input, int len);
int get_action(float input[]);


#endif
