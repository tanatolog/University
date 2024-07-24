#include <stdio.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include "cublas_v2.h"
#pragma comment (lib, "cublas.lib")
#include <ctime>
#include <chrono> 
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

#define num 10 // num - количество корней 20000

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

__global__ void Transpose(double* Array, unsigned long int N)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > N * N) { return; }
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	if (q < w) {
		Array[w * N + q] = Array[ind] - Array[w * N + q];
		Array[ind] = 0;
	}
}

__global__ void fillone(double* Array)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > num) { return; }
	Array[ind] = 1.0f;
}

/*__global__ void ParalelSolve(double* L, double* B, double* X, unsigned long int N)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > N * N) { return; }
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	for (unsigned long int j = 0; j < N; j++) {
		if (w == j) { X[j] = B[j] / L[j * N + j]; }
		__syncthreads();
		for (unsigned long int i = j + 1; i < N; i++) {
			if ((q == i) && (w == j)) { B[i] = B[i] - L[i * num + j] * X[j]; }
		}
		__syncthreads(); 
	}
}*/

__global__ void Paralel1(double* L, double* B, double* X, unsigned long int N, unsigned long int j)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > N) { return; }
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	if (w == j) { X[j] = B[j] / L[j * N + j]; }
	__syncthreads();
}

__global__ void Paralel2(double* L, double* B, double* X, unsigned long int N, unsigned long int j, unsigned long int i)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > N * N) { return; }
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	if ((q == i) && (w == j)) { B[i] = B[i] - L[i * num + j] * X[j]; }
	__syncthreads();
}

void ParalelSolve(double* L, double* B, double* X, unsigned long int N)
{
	dim3 threads = dim3(1024, 1);
	dim3 blocks = dim3((N * N/ threads.x) + 1, 1);
	for (unsigned long int j = 0; j < N; j++) {
		Paralel1 << < blocks, threads >> > (L, B, X, N, j);
		for (unsigned long int i = j + 1; i < N; i++) {
			Paralel2 << < blocks, threads >> > (L, B, X, N, j, i);
		}
	}
}

void LinelSolve(double* L, double* B, double* X, unsigned long int N)
{
	for (unsigned long int j = 0; j < N; j++) {
		X[j] = B[j] / L[j * N + j];
		for (unsigned long int i = j + 1; i < N; i++) {
			B[i] = B[i] - L[i * num + j] * X[j];
		}
	}
}

int main(void)
{
	setlocale(0, "");
	cudaEvent_t start, stop;
	cublasHandle_t handle;                              // CUBLAS context
	unsigned long int j, n = num;
	double* a = (double*)malloc(n * n * sizeof(*a));    // nxn matrix a on the host
	double* x = (double*)malloc(n * sizeof(*x));        // n - vector x on the host
	double* y = (double*)malloc(n * sizeof(*y));
	double* O = (double*)malloc(n * n * sizeof(*O));
	float gpuTime = 0;

	double* d_a = NULL; // d_a - a on the device
	double* d_x = NULL; // d_x - x on the device
	double* d_y = NULL;
	double* d_O = NULL;

	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_a, n * n * sizeof(*a))); // device memory alloc for a
	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_x, n * sizeof(*x)));     // device memory alloc for x
	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_y, n * sizeof(*y)));
	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_O, n * n * sizeof(*O)));
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

	CUDA_CHECK_ERROR(cudaMemcpy(x, d_x, n * sizeof(*x), cudaMemcpyDeviceToHost));
	printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << x[j] << endl;
	}
	cout << endl;

	threads = dim3(1024, 1);
	blocks = dim3((n * n / threads.x) + 1, 1);
	Transpose << < blocks, threads >> > (d_a, n);

	blocks = dim3((n / threads.x) + 1, 1);
	fillone << < blocks, threads >> > (d_y);

	CUDA_CHECK_ERROR(cudaDeviceSynchronize());

	CUDA_CHECK_ERROR(cudaMemcpy(a, d_a, n * n * sizeof(*a), cudaMemcpyDeviceToHost));
	CUDA_CHECK_ERROR(cudaMemcpy(y, d_y, n * sizeof(*y), cudaMemcpyDeviceToHost));

	/*cout << "Матрица a: \n";
	for (int h = 0; h < n * n; h++) {
	  cout << setprecision(3) << a[h] << " ";
	  if ((h % n) == (n - 1)) cout << endl;
	}
	cout << "\n"; */

	threads = dim3(1024, 1);
	blocks = dim3((n * n / threads.x) + 1, 1);

	CUDA_CHECK_ERROR(cudaEventCreate(&start));
	CUDA_CHECK_ERROR(cudaEventCreate(&stop));
	CUDA_CHECK_ERROR(cudaEventRecord(start, 0));

	//ParalelSolve (d_a, d_y, d_O, n);

	CUDA_CHECK_ERROR(cudaEventRecord(stop, 0));
	CUDA_CHECK_ERROR(cudaEventSynchronize(stop));
	CUDA_CHECK_ERROR(cudaEventElapsedTime(&gpuTime, start, stop));
	CUDA_CHECK_ERROR(cudaEventDestroy(start));
	CUDA_CHECK_ERROR(cudaEventDestroy(stop));

	CUDA_CHECK_ERROR(cudaDeviceSynchronize());

	cout << setprecision(6) << "Для вычисления понадобилось " << gpuTime << " милисекунд\n";

	CUDA_CHECK_ERROR(cudaMemcpy(O, d_O, n * sizeof(*O), cudaMemcpyDeviceToHost));
	printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << O[j] << endl;
	}

	auto start_time = chrono::steady_clock::now();

	LinelSolve(a, y, O, n);

	auto end_time = chrono::steady_clock::now();
	auto elapsed_ns = chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << setprecision(6) << "Для вычисления понадобилось " << elapsed_ns.count()* 0.000001 << " милисекунд\n";

	/*printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << O[j] << endl;
	}*/

	CUDA_CHECK_ERROR(cudaFree(d_a));               // free device memory
	CUDA_CHECK_ERROR(cudaFree(d_x));               // free device memory 
	CUBLAS_CHECK_ERROR(cublasDestroy_v2(handle));                      // destroy CUBLAS context
	free(a);                                       // freе host memory
	free(x);                                       // free host memory

	return EXIT_SUCCESS;
}