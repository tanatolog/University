#include <stdio.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include "cublas_v2.h"
#pragma comment (lib, "cublas.lib")
using namespace std;

#define CUDA_CHECK_ERROR(err)           \
if (err != cudaSuccess) {          \
printf("Ошибка CUDA: %s\n", cudaGetErrorString(err));    \
printf("В файле: %s, на строке: %i\n", __FILE__, __LINE__);  \
}                 \

#define CUBLAS_CHECK_ERROR(err)           \
if (err != CUBLAS_STATUS_SUCCESS) {          \
printf("Ошибка cuBLAS: %s\n", err);    \
printf("В файле: %s, на строке: %i\n", __FILE__, __LINE__);  \
}                 \

#define num 5000 // num - количество корней 20000

__global__ void Create(double* Array, unsigned long int N)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > N * N) { return; }
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	if (q > w) {
		Array[ind] = 0;
	}
	else {
		double tmp = 1 + 0.2 * ind;
		Array[ind] = tmp;
	}
}

__global__ void fillone(double* Array)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > num) { return; }
	Array[ind] = 1.0f;
}

int main(void)
{
	setlocale(0, "");
	cudaEvent_t start, stop;
	cublasHandle_t handle;                              // CUBLAS context
	unsigned long int j, n = num;
	double* a = (double*)malloc(n * n * sizeof(*a));    // nxn matrix a on the host
	double* x = (double*)malloc(n * sizeof(*x));        // n - vector x on the host
	float gpuTime = 0;

	double* d_a = NULL; // d_a - a on the device
	double* d_x = NULL; // d_x - x on the device

	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_a, n * n * sizeof(*a))); // device memory alloc for a
	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_x, n * sizeof(*x)));     // device memory alloc for x
	CUBLAS_CHECK_ERROR(cublasCreate_v2(&handle));                   // initialize CUBLAS context

	dim3 threads = dim3(1024, 1);
	dim3 blocks = dim3((n * n / threads.x) + 1, 1);
	Create << < blocks, threads >> > (d_a, n);

	blocks = dim3((n / threads.x) + 1, 1);
	fillone << < blocks, threads >> > (d_x);

	/*CUDA_CHECK_ERROR(cudaMemcpy(a, d_a, n * n * sizeof(*a), cudaMemcpyDeviceToHost));
	cout << "Матрица a: \n";
	for (int h = 0; h < n * n; h++) {
		cout << fixed << setprecision(3) << a[h] << " ";
		if ((h % n) == (n - 1)) cout << endl;
	}
	cout << "\n"; */

	CUDA_CHECK_ERROR(cudaEventCreate(&start));
	CUDA_CHECK_ERROR(cudaEventCreate(&stop));
	CUDA_CHECK_ERROR(cudaEventRecord(start, 0));

	CUBLAS_CHECK_ERROR(cublasDtrsv(handle, CUBLAS_FILL_MODE_LOWER, CUBLAS_OP_N, CUBLAS_DIAG_NON_UNIT, n, d_a, n, d_x, 1));

	CUDA_CHECK_ERROR(cudaEventRecord(stop, 0));
	CUDA_CHECK_ERROR(cudaEventSynchronize(stop));
	CUDA_CHECK_ERROR(cudaEventElapsedTime(&gpuTime, start, stop));
	CUDA_CHECK_ERROR(cudaEventDestroy(start));
	CUDA_CHECK_ERROR(cudaEventDestroy(stop));

	cout << setprecision(6) << "Для вычисления понадобилось " << gpuTime << " милисекунд\n";

	CUDA_CHECK_ERROR(cudaDeviceSynchronize());

	/*CUDA_CHECK_ERROR(cudaMemcpy(x, d_x, n * sizeof(*x), cudaMemcpyDeviceToHost));
	printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << x[j] << endl;
	}
	cout << endl;*/

	CUDA_CHECK_ERROR(cudaFree(d_a));               // free device memory
	CUDA_CHECK_ERROR(cudaFree(d_x));               // free device memory 
	CUBLAS_CHECK_ERROR(cublasDestroy_v2(handle));  // destroy CUBLAS context
	free(a);                                       // freе host memory
	free(x);                                       // free host memory
	cin.get();
	return EXIT_SUCCESS;
}




























































