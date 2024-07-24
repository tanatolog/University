#include <stdio.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <ctime>
#include <chrono> 
using namespace std;

#define CUDA_CHECK_ERROR(err)           \
if (err != cudaSuccess) {          \
printf("Ошибка CUDA: %s\n", cudaGetErrorString(err));    \
printf("В файле: %s, на строке: %i\n", __FILE__, __LINE__);  \
}                 \

#define num 5000 // num - количество корней 20000
#define threads_ 1024 // threads_ - количество нитей в блоке 1024


__global__ void Create(double* Array, unsigned long int N)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind > N * N) { return; }
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	if (q < w) {
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

__global__ void ParalelK1(double* L, double* B, double* X, unsigned long int N, unsigned long int j)
{
	unsigned long int ind = blockIdx.x * blockDim.x + threadIdx.x;
	if (ind == 0) {
		X[j] = B[j] / L[j * N + j];
	}
}

__global__ void ParalelK2(double* L, double* B, double* X, unsigned long int N, unsigned long int j, unsigned long int i)
{
	unsigned long int ind = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned long int w = (ind % N);
	unsigned long int q = (ind / N);
	__shared__ float tmpX;
	__shared__ unsigned long int T;
	if (threadIdx.x == 0) {
		tmpX = X[j];
		T = N;
	}
	__syncthreads();
	if (w == i) {
		B[q] = B[q] - L[q * T + j] * tmpX;
	}
	__syncthreads();
}

void ParalelSolve(double* L, double* B, double* X, unsigned long int N)
{
	dim3 threads = dim3(threads_, 1);
	dim3 blocks = dim3((N * N / threads.x) + 1, 1);
	for (unsigned long int j = 0; j < N; j++) {
		ParalelK1 << < 1, 1 >> > (L, B, X, N, j);
		unsigned long int i = j + 1;
		ParalelK2 << < blocks, threads >> > (L, B, X, N, j, i);
	}
}

__global__ void ParalelSolveK(double* L, double* B, double* X, unsigned long int N)
{
	int ind = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned long int q = (ind / N);
	unsigned long int w = (ind % N);
	__shared__ float tmpX;
	__shared__ float tmpB;
	for (unsigned long int j = 0; j < N; j++) {
		if (threadIdx.x == 0) {
			tmpX = X[j];
			tmpB = B[j];
		}
		__syncthreads();
		if (ind == 0) { tmpX = tmpB / L[j * N + j]; }
		__syncthreads();
		if (threadIdx.x == 0) {
			X[j] = tmpX;
		}
		unsigned long int i = j + 1;
		__syncthreads();
		if (w == i) { B[q] = B[q] - L[q * N + j] * tmpX; }
		__syncthreads();
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
	unsigned long int j = 0, n = num;
	double* a = (double*)malloc(n * n * sizeof(*a));    // nxn matrix a on the host       
	double* y = (double*)malloc(n * sizeof(*y));
	double* O = (double*)malloc(n * n * sizeof(*O));
	unsigned int* P = (unsigned int*)malloc(sizeof(*P));
	float gpuTime = 0;

	double* d_a = NULL; // d_a - a on the device
	double* d_y = NULL;
	double* d_O = NULL;

	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_a, n * n * sizeof(*a))); // device memory alloc for a
	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_y, n * sizeof(*y)));
	CUDA_CHECK_ERROR(cudaMalloc((void**)&d_O, n * n * sizeof(*O)));

	dim3 threads = dim3(threads_, 1);
	dim3 blocks = dim3((n * n / threads.x) + 1, 1);
	Create << < blocks, threads >> > (d_a, n);

	blocks = dim3((n / threads.x) + 1, 1);
	fillone << < blocks, threads >> > (d_y);

	/*CUDA_CHECK_ERROR(cudaMemcpy(a, d_a, n * n * sizeof(*a), cudaMemcpyDeviceToHost));
	cout << "Матрица a: \n";
	for (j = 0; j < n * n; j++) {
		cout << fixed << setprecision(3) << a[j] << " ";
		if ((j % n) == (n - 1)) cout << endl;
	}
	cout << "\n";*/

	CUDA_CHECK_ERROR(cudaDeviceSynchronize());

	CUDA_CHECK_ERROR(cudaMemcpy(a, d_a, n * n * sizeof(*a), cudaMemcpyDeviceToHost));
	CUDA_CHECK_ERROR(cudaMemcpy(y, d_y, n * sizeof(*y), cudaMemcpyDeviceToHost));

	CUDA_CHECK_ERROR(cudaEventCreate(&start));
	CUDA_CHECK_ERROR(cudaEventCreate(&stop));
	CUDA_CHECK_ERROR(cudaEventRecord(start, 0));

	//blocks = dim3((n * n / threads.x) + 1, 1);

	//ParalelSolveK << < blocks, threads >> > (d_a, d_y, d_O, n);

	ParalelSolve (d_a, d_y, d_O, n);

	CUDA_CHECK_ERROR(cudaEventRecord(stop, 0));
	CUDA_CHECK_ERROR(cudaEventSynchronize(stop));
	CUDA_CHECK_ERROR(cudaEventElapsedTime(&gpuTime, start, stop));
	CUDA_CHECK_ERROR(cudaEventDestroy(start));
	CUDA_CHECK_ERROR(cudaEventDestroy(stop));

	CUDA_CHECK_ERROR(cudaDeviceSynchronize());

	cout << setprecision(6) << "Для вычисления понадобилось " << gpuTime << " милисекунд\n";

	/*CUDA_CHECK_ERROR(cudaMemcpy(O, d_O, n * sizeof(*O), cudaMemcpyDeviceToHost));
	printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << O[j] << endl;
	}*/

	/*CUDA_CHECK_ERROR(cudaMemcpy(O, d_y, n * sizeof(*O), cudaMemcpyDeviceToHost));
	printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << O[j] << endl;
	}*/

	auto start_time = chrono::steady_clock::now();

	//LinelSolve(a, y, O, n);

	auto end_time = chrono::steady_clock::now();
	auto elapsed_ns = chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	//cout << setprecision(6) << "Для вычисления понадобилось " << elapsed_ns.count() * 0.000001 << " милисекунд\n";

	/*printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << O[j] << endl;
	}*/

	/*printf("Решение:\n");
	for (j = 0; j < n; j++) {
		cout << j << " " << setprecision(6) << y[j] << endl;
	}*/

	CUDA_CHECK_ERROR(cudaFree(d_a));               // free device memory
	CUDA_CHECK_ERROR(cudaFree(d_y));               // free device memory 
	CUDA_CHECK_ERROR(cudaFree(d_O));
	free(a);                                       // freе host memory
	free(y);                                       // free host memory
	free(O);
	cin.get();

	return EXIT_SUCCESS;
}