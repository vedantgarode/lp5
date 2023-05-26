#include <stdio.h>
#include <stdlib.h>
#define N 5
__global__ void add(int *a, int *b, int *c) {
int i = blockIdx.x * blockDim.x + threadIdx.x;
if (i < N) {
c[i] = a[i] + b[i];
}
}
int main() {
int a[N] = {1, 2, 3, 4, 5};
int b[N] = {6, 7, 8, 9, 10};
int c[N] = {0};
int *dev_a, *dev_b, *dev_c;
cudaMalloc((void **)&dev_a, N * sizeof(int));
cudaMalloc((void **)&dev_b, N * sizeof(int));
cudaMalloc((void **)&dev_c, N * sizeof(int));
cudaMemcpy(dev_a, a, N * sizeof(int), cudaMemcpyHostToDevice);
cudaMemcpy(dev_b, b, N * sizeof(int), cudaMemcpyHostToDevice);
add<<<1, N>>>(dev_a, dev_b, dev_c);
cudaMemcpy(c, dev_c, N * sizeof(int), cudaMemcpyDeviceToHost);
for (int i = 0; i < N; i++) {
//printf("%d ", c[i]);
printf("%d + %d = %d\n", a[i], b[i], c[i]);
}
printf("\n");
cudaFree(dev_a);
cudaFree(dev_b);
cudaFree(dev_c);
return 0;
}