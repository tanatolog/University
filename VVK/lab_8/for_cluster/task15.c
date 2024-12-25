#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 15
#define N 1190 // Adjust N to control the size of the matrices

/*Implement Matrix_Multiply*/
void Matrix_Multiply(float* A, float* B, float* C, int m, int n, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            C[i * p + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i * p + j] += A[i * n + k] * B[k * p + j];
            }
        }
    }
}

void Parallel_Matrix_Multiply(int rank, int size, float* A, float* B, float* C) {
    double start_time; // Время начала выполнения
    double end_time; // Время завершения выполнения

    int m = N; // Number of rows in matrices A and C.
    int n = N; // Number of columns in A and rows in B.
    int p = N; // Number of columns in matrices B and C.

    // Determine the number of rows each process will handle
    int rows_per_proc = m / size;
    int remainder = m % size;

    // Calculate local_m and offset for each process
    int local_m;
    int offset;
    if (rank < remainder) {
        local_m = rows_per_proc + 1;
        offset = rank * local_m;
    }
    else {
        local_m = rows_per_proc;
        offset = rank * local_m + remainder;
    }

    // Allocate memory for local matrices
    float* local_A = (float*)malloc(local_m * n * sizeof(float));
    float* local_C = (float*)malloc(local_m * p * sizeof(float));

    if (local_A == NULL || local_C == NULL) {
        fprintf(stderr, "Memory allocation failed in process %d\n", rank);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (rank == 0) {
        start_time = MPI_Wtime(); // Засекаем время начала выполнения

        // Send data to other processes
        for (int dest = 1; dest < size; dest++) {
            int dest_local_m = (dest < remainder) ? rows_per_proc + 1 : rows_per_proc;
            int dest_offset = (dest < remainder) ? dest * dest_local_m : dest * dest_local_m + remainder;

            MPI_Send(&dest_local_m, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            MPI_Send(&A[dest_offset * n], dest_local_m * n, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
            MPI_Send(B, n * p, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
        }

        // Copy process 0's portion of A into local_A
        for (int i = 0; i < local_m * n; i++) {
            local_A[i] = A[offset * n + i];
        }
    }
    else {
        // Receive data from process 0
        MPI_Recv(&local_m, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        free(local_A); // Reallocate memory based on received size
        local_A = (float*)malloc(local_m * n * sizeof(float));
        MPI_Recv(local_A, local_m * n, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        B = (float*)malloc(n * p * sizeof(float));
        MPI_Recv(B, n * p, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Each process performs local matrix multiplication
    Matrix_Multiply(local_A, B, local_C, local_m, n, p);

    // Gather results at process 0
    if (rank == 0) {
        for (int i = 0; i < local_m * p; i++) {
            C[offset * p + i] = local_C[i];
        }

        for (int src = 1; src < size; src++) {
            int src_local_m = (src < remainder) ? rows_per_proc + 1 : rows_per_proc;
            int src_offset = (src < remainder) ? src * src_local_m : src * src_local_m + remainder;

            MPI_Recv(&C[src_offset * p], src_local_m * p, MPI_FLOAT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        end_time = MPI_Wtime(); // Засекаем время окончания выполнения
        printf("%f ", end_time - start_time); // Вывод времени выполнения
    }
    else {
        MPI_Send(local_C, local_m * p, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        free(B);
    }

    // Free local memory
    free(local_A);
    free(local_C);
}



int main(int argc, char** argv) {
    int rank, size;
    float* A = NULL;
    float* B = NULL;
    float* C = NULL;
    int m = N; // Number of rows in matrices A and C.
    int n = N; // Number of columns in A and rows in B.
    int p = N; // Number of columns in matrices B and C.

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes and the rank of this process
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Allocate memory for A, B, C, and C_serial
        A = (float*)malloc(m * n * sizeof(float));
        B = (float*)malloc(n * p * sizeof(float));
        C = (float*)malloc(m * p * sizeof(float));

        if (A == NULL || B == NULL || C == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        // Fill matrix A and B with numbers
        for (int i = 0; i < m * n; i++) {
            A[i] = i;
        }
        for (int i = 0; i < n * p; i++) {
            B[i] = i;
        }

        printf("Start test W%d\n", MATRIX_SIZE);
    }

    Parallel_Matrix_Multiply(rank, size, A, B, C);
    Parallel_Matrix_Multiply(rank, size, A, B, C);
    Parallel_Matrix_Multiply(rank, size, A, B, C);

    if (rank == 0) {
        free(A);
        free(B);
        free(C);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}