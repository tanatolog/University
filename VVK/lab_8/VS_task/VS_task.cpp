#include<stdio.h>
#include<mpi.h>

#define MATRIX_SIZE 5
#define NUM_ROWS_A 2000 // Определение количества строк в матрице A
#define NUM_COLUMNS_A 2000 // Определение количества столбцов в матрице A
#define NUM_ROWS_B 2000 // Определение количества строк в матрице B
#define NUM_COLUMNS_B 2000 // Определение количества столбцов в матрице B
#define MASTER_TO_SLAVE_TAG 1 // Тег для сообщений от мастера к рабочим процессам
#define SLAVE_TO_MASTER_TAG 4 // Тег для сообщений от рабочих процессов к мастеру

int rank; // Ранг процесса в MPI
int size; // Общее количество процессов в MPI
int i, j, k; // Вспомогательные переменные для циклов
double mat_a[NUM_ROWS_A][NUM_COLUMNS_A]; // Матрица A
double mat_b[NUM_ROWS_B][NUM_COLUMNS_B]; // Матрица B
double mat_result[NUM_ROWS_A][NUM_COLUMNS_B]; // Матрица результата C
double start_time; // Время начала выполнения
double end_time; // Время завершения выполнения
int low_bound; // Нижняя граница для строк, выделенных рабочему процессу
int upper_bound; // Верхняя граница для строк, выделенных рабочему процессу
int portion; // Количество строк, которое получает каждый рабочий процесс
MPI_Status status; // Статус для функции MPI_Recv
MPI_Request request; // Запрос для функции MPI_Isend

// Функция для генерации матриц A и B
void MasterMakeAB()
{
    if (rank == 0) {
        for (i = 0; i < NUM_ROWS_A; i++) {
            for (j = 0; j < NUM_COLUMNS_A; j++) {
                mat_a[i][j] = i + j; // Заполнение матрицы A
            }
        }
        for (i = 0; i < NUM_ROWS_B; i++) {
            for (j = 0; j < NUM_COLUMNS_B; j++) {
                mat_b[i][j] = i + j; // Заполнение матрицы B
            }
        }
        printf("Start test W%d\n", MATRIX_SIZE);
    }
}

// Функция для печати матриц A, B и C
void printArray()
{
    for (i = 0; i < NUM_ROWS_A; i++) {
        printf("\n");
        for (j = 0; j < NUM_COLUMNS_A; j++)
            printf("%8.2f  ", mat_a[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < NUM_ROWS_B; i++) {
        printf("\n");
        for (j = 0; j < NUM_COLUMNS_B; j++)
            printf("%8.2f  ", mat_b[i][j]);
    }
    printf("\n\n\n");
    for (i = 0; i < NUM_ROWS_A; i++) {
        printf("\n");
        for (j = 0; j < NUM_COLUMNS_B; j++)
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
            portion = (NUM_ROWS_A / (size - 1)); // Вычисление количества строк, которое получит каждый рабочий процесс
            low_bound = (i - 1) * portion; // Нижняя граница для строки, которую получит рабочий процесс
            if (((i + 1) == size) && ((NUM_ROWS_A % (size - 1)) != 0)) { // Если строки не делятся нацело
                upper_bound = NUM_ROWS_A; // Последний процесс получает все оставшиеся строки
            }
            else {
                upper_bound = low_bound + portion; // Строки равномерно распределяются между рабочими процессами
            }
            // Отправка нижней границы без блокировки
            MPI_Isend(&low_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &request);
            // Отправка верхней границы без блокировки
            MPI_Isend(&upper_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &request);
            // Отправка части матрицы A без блокировки
            MPI_Isend(&mat_a[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_A, MPI_DOUBLE, i, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &request);
        }
    }
    // Рассылка матрицы B всем рабочим процессам
    MPI_Bcast(&mat_b, NUM_ROWS_B * NUM_COLUMNS_B, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Работа рабочих процессов */
    if (rank > 0) {
        // Получение нижней границы от мастера
        MPI_Recv(&low_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &status);
        // Получение верхней границы от мастера
        MPI_Recv(&upper_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &status);
        // Получение части матрицы A для обработки
        MPI_Recv(&mat_a[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_A, MPI_DOUBLE, 0, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &status);
        for (i = low_bound; i < upper_bound; i++) { // Перебор строк матрицы A
            for (j = 0; j < NUM_COLUMNS_B; j++) { // Перебор столбцов матрицы B
                for (k = 0; k < NUM_ROWS_B; k++) { // Перебор строк матрицы B
                    mat_result[i][j] += (mat_a[i][k] * mat_b[k][j]); // Вычисление элемента результата C
                }
            }
        }
        // Отправка нижней границы обратно на мастер
        MPI_Isend(&low_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &request);
        // Отправка верхней границы обратно на мастер
        MPI_Isend(&upper_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &request);
        // Отправка обработанных данных обратно на мастер
        MPI_Isend(&mat_result[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_B, MPI_DOUBLE, 0, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &request);
    }

    /* Мастер собирает обработанные данные */
    if (rank == 0) {
        for (i = 1; i < size; i++) { // Сбор данных от всех рабочих процессов
            // Получение нижней границы от рабочего процесса
            MPI_Recv(&low_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &status);
            // Получение верхней границы от рабочего процесса
            MPI_Recv(&upper_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &status);
            // Получение обработанных данных от рабочего процесса
            MPI_Recv(&mat_result[low_bound][0], (upper_bound - low_bound) * NUM_COLUMNS_B, MPI_DOUBLE, i, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &status);
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

    MasterMakeAB();
    ParallelMul();
    ParallelMul();
    ParallelMul();

    MPI_Finalize(); // Завершение работы MPI
    return 0;
}