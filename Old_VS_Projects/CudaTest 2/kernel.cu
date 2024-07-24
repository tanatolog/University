#include <cuda.h>
#include <curand_kernel.h>
#include <stdio.h>
#include <time.h>

#define N 10

__global__ void setup_kernel(curandState* state, unsigned long seed)
{
    int id = threadIdx.x;
    curand_init(seed, id, 0, &state[id]);
}

__global__ void generate(curandState* globalState, float* randomArray)
{
    int ind = threadIdx.x;
    curandState localState = globalState[ind];
    float RANDOM = curand_uniform(&localState);
    randomArray[ind] = RANDOM;
    globalState[ind] = localState;
}

int main(int argc, char** argv)
{
    dim3 tpb(N, 1);
    curandState* devStates;
    float* randomValues = new float[N];
    float* devRandomValues;

    cudaMalloc(&devStates, N * sizeof(curandState));
    cudaMalloc(&devRandomValues, N * sizeof(*randomValues));// setup seeds
    setup_kernel << <1, N >> > (devStates, time(NULL));

    printf("%s\n", cudaGetErrorString(cudaGetLastError()));// generate random numbers
    generate << <1, N >> > (devStates, devRandomValues);

    printf("%s\n", cudaGetErrorString(cudaGetLastError()));

    cudaMemcpy(randomValues, devRandomValues, N * sizeof(*randomValues), cudaMemcpyDeviceToHost);
    for (int i = 0; i < N; i++)
    {
        printf("%f\n", randomValues[i]);
    }

    cudaFree(devRandomValues);
    cudaFree(devStates);
    delete randomValues;
    getchar();
    return 0;
}