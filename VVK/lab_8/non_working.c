#include<stdio.h>
#include<mpi.h>
#include <stdlib.h> // Для malloc и free

#define MASTER_TO_SLAVE_TAG 1 // Тег для сообщений от мастера к рабочим процессам
#define SLAVE_TO_MASTER_TAG 4 // Тег для сообщений от рабочих процессов к мастеру

int num_rows_a = 100; // Определение количества строк в матрице A
int num_columns_a = 100; // Определение количества столбцов в матрице A
int num_rows_b = 100; // Определение количества строк в матрице B
int num_columns_b = 100; // Определение количества столбцов в матрице B
int rank; // Ранг процесса в MPI
int size; // Общее количество процессов в MPI
int i, j, k; // Вспомогательные переменные для циклов
double** mat_a;    // Матрица A
double** mat_b;    // Матрица B
double** mat_result; // Матрица результата C
double start_time; // Время начала выполнения
double end_time; // Время завершения выполнения
int low_bound; // Нижняя граница для строк, выделенных рабочему процессу
int upper_bound; // Верхняя граница для строк, выделенных рабочему процессу
int portion; // Количество строк, которое получает каждый рабочий процесс
MPI_Status status; // Статус для функции MPI_Recv
MPI_Request request; // Запрос для функции MPI_Isend

// Функция для выделения памяти под матрицу
double** allocateMatrix(int rows, int columns) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(columns * sizeof(double));
    }
    return matrix;
}

// Функция для освобождения памяти матрицы
void freeMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функция для генерации матриц A и B
void MasterMakeAB(int num) {
    // Освобождаем предыдущие матрицы, если они уже были выделены
    if (mat_a) freeMatrix(mat_a, num_rows_a);
    if (mat_b) freeMatrix(mat_b, num_rows_b);
    if (mat_result) freeMatrix(mat_result, num_rows_a);

    num_rows_a = num_columns_a = num_rows_b = num_columns_b = 10;

    switch (num) {
    case 1: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 220; break;
    case 2: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 310; break;
    case 3: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 380; break;
    case 4: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 450; break;
    case 5: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 500; break;
    case 6: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 550; break;
    case 7: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 590; break;
    case 8: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 630; break;
    case 9: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 670; break;
    case 10: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 700; break;
    case 11: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 740; break;
    case 12: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 770; break;
    case 13: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 800; break;
    case 14: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 840; break;
    case 15: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 870; break;
    case 16: num_rows_a = num_columns_a = num_rows_b = num_columns_b = 890; break;
    }

    // Выделяем память под матрицы
    mat_a = allocateMatrix(num_rows_a, num_columns_a);
    mat_b = allocateMatrix(num_rows_b, num_columns_b);
    mat_result = allocateMatrix(num_rows_a, num_columns_b);

    if (rank == 0) {
        for (i = 0; i < num_rows_a; i++)
            for (j = 0; j < num_columns_a; j++)
                mat_a[i][j] = i + j;

        for (i = 0; i < num_rows_b; i++)
            for (j = 0; j < num_columns_b; j++)
                mat_b[i][j] = i + j;
    }
}

// Функция для печати матриц A, B и C
void printArray()
{
    for (i = 0; i < num_rows_a; i++) {
        printf("\n");
        for (j = 0; j < num_columns_a; j++)
            printf("%8.2f  ", mat_a[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < num_rows_b; i++) {
        printf("\n");
        for (j = 0; j < num_columns_b; j++)
            printf("%8.2f  ", mat_b[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < num_rows_a; i++) {
        printf("\n");
        for (j = 0; j < num_columns_b; j++)
            printf("%8.2f  ", mat_result[i][j]);
    }
    printf("\n\n");
}

// Параллельный алгоритм умножения матриц
void ParallelMul()
{
    /* Инициализация работы на мастере */
    if (rank == 0) {
        start_time = MPI_Wtime(); // Засекаем время начала выполнения
        for (i = 1; i < size; i++) { // Распределение работы среди рабочих процессов
            portion = (num_rows_a / (size - 1)); // Вычисление количества строк, которое получит каждый рабочий процесс
            low_bound = (i - 1) * portion; // Нижняя граница для строки, которую получит рабочий процесс
            if (((i + 1) == size) && ((num_rows_a % (size - 1)) != 0)) { // Если строки не делятся нацело
                upper_bound = num_rows_a; // Последний процесс получает все оставшиеся строки
            }
            else {
                upper_bound = low_bound + portion; // Строки равномерно распределяются между рабочими процессами
            }
            // Отправка нижней границы без блокировки
            MPI_Isend(&low_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &request);
            // Отправка верхней границы без блокировки
            MPI_Isend(&upper_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &request);
            // Отправка части матрицы A без блокировки
            MPI_Isend(&mat_a[low_bound][0], (upper_bound - low_bound) * num_columns_a, MPI_DOUBLE, i, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &request);
        }
    }
    // Рассылка матрицы B всем рабочим процессам
    MPI_Bcast(&mat_b, num_rows_b * num_columns_b, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Работа рабочих процессов */
    if (rank > 0) {
        // Получение нижней границы от мастера
        MPI_Recv(&low_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &status);
        // Получение верхней границы от мастера
        MPI_Recv(&upper_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &status);
        // Получение части матрицы A для обработки
        MPI_Recv(&mat_a[low_bound][0], (upper_bound - low_bound) * num_columns_a, MPI_DOUBLE, 0, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &status);
        for (i = low_bound; i < upper_bound; i++) { // Перебор строк матрицы A
            for (j = 0; j < num_columns_b; j++) { // Перебор столбцов матрицы B
                for (k = 0; k < num_rows_b; k++) { // Перебор строк матрицы B
                    mat_result[i][j] += (mat_a[i][k] * mat_b[k][j]); // Вычисление элемента результата C
                }
            }
        }
        // Отправка нижней границы обратно на мастер
        MPI_Isend(&low_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &request);
        // Отправка верхней границы обратно на мастер
        MPI_Isend(&upper_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &request);
        // Отправка обработанных данных обратно на мастер
        MPI_Isend(&mat_result[low_bound][0], (upper_bound - low_bound) * num_columns_b, MPI_DOUBLE, 0, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &request);
    }

    /* Мастер собирает обработанные данные */
    if (rank == 0) {
        for (i = 1; i < size; i++) { // Сбор данных от всех рабочих процессов
            // Получение нижней границы от рабочего процесса
            MPI_Recv(&low_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &status);
            // Получение верхней границы от рабочего процесса
            MPI_Recv(&upper_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &status);
            // Получение обработанных данных от рабочего процесса
            MPI_Recv(&mat_result[low_bound][0], (upper_bound - low_bound) * num_columns_b, MPI_DOUBLE, i, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &status);
        }
        end_time = MPI_Wtime(); // Засекаем время окончания выполнения
        printf("%f ", end_time - start_time); // Вывод времени выполнения
        //printArray(); // Печать результата
    }
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv); // Инициализация MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получение ранга текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Получение общего числа процессов

    MasterMakeAB(1);
    ParallelMul();
    MasterMakeAB(2);
    ParallelMul();
    MasterMakeAB(3);
    ParallelMul();
    MasterMakeAB(4);
    ParallelMul();
    MasterMakeAB(5);
    ParallelMul();
    MasterMakeAB(6);
    ParallelMul();
    MasterMakeAB(7);
    ParallelMul();
    MasterMakeAB(8);
    ParallelMul();
    MasterMakeAB(9);
    ParallelMul();
    MasterMakeAB(10);
    ParallelMul();
    MasterMakeAB(11);
    ParallelMul();
    MasterMakeAB(12);
    ParallelMul();
    MasterMakeAB(13);
    ParallelMul();
    MasterMakeAB(14);
    ParallelMul();
    MasterMakeAB(15);
    ParallelMul();
    MasterMakeAB(16);
    ParallelMul();
    MasterMakeAB(1);
    ParallelMul();
    MasterMakeAB(2);
    ParallelMul();
    MasterMakeAB(3);
    ParallelMul();
    MasterMakeAB(4);
    ParallelMul();
    MasterMakeAB(5);
    ParallelMul();
    MasterMakeAB(6);
    ParallelMul();
    MasterMakeAB(7);
    ParallelMul();
    MasterMakeAB(8);
    ParallelMul();
    MasterMakeAB(9);
    ParallelMul();
    MasterMakeAB(10);
    ParallelMul();
    MasterMakeAB(11);
    ParallelMul();
    MasterMakeAB(12);
    ParallelMul();
    MasterMakeAB(13);
    ParallelMul();
    MasterMakeAB(14);
    ParallelMul();
    MasterMakeAB(15);
    ParallelMul();
    MasterMakeAB(16);
    ParallelMul();
    MasterMakeAB(1);
    ParallelMul();
    MasterMakeAB(2);
    ParallelMul();
    MasterMakeAB(3);
    ParallelMul();
    MasterMakeAB(4);
    ParallelMul();
    MasterMakeAB(5);
    ParallelMul();
    MasterMakeAB(6);
    ParallelMul();
    MasterMakeAB(7);
    ParallelMul();
    MasterMakeAB(8);
    ParallelMul();
    MasterMakeAB(9);
    ParallelMul();
    MasterMakeAB(10);
    ParallelMul();
    MasterMakeAB(11);
    ParallelMul();
    MasterMakeAB(12);
    ParallelMul();
    MasterMakeAB(13);
    ParallelMul();
    MasterMakeAB(14);
    ParallelMul();
    MasterMakeAB(15);
    ParallelMul();
    MasterMakeAB(16);
    ParallelMul();

    MPI_Finalize(); // Завершение работы MPI
    return 0;
}