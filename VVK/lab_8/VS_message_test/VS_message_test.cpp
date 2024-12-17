#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    int send_data = 123, recv_data;

    // Инициализация MPI
    MPI_Init(&argc, &argv);

    // Получение ранга и размера коммуникатора
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Проверяем, что запущено хотя бы два процесса
    if (size < 2) {
        printf("Error: need more than 2 processes\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Bcast(&send_data, 1, MPI_INT, 0, MPI_COMM_WORLD);  // Рассылка данных всем от процесса 0

    // Процесс с рангом 0 отправляет данные процессу с рангом 1
    if (rank == 0) {
        printf("Proc %d: send (%d) to proc 1\n", rank, send_data);
        MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);  // Отправка данных
    }
    else if (rank == 1) {
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // Получение данных
        printf("Proc %d: recv (%d) to proc 0\n", rank, recv_data);
    }

    // Барьер: синхронизация процессов
    MPI_Barrier(MPI_COMM_WORLD);

    // Все процессы выполнят этот вывод, когда дойдут до барьера
    printf("Proc %d: barrier passed\n", rank);

    // Завершаем работу с MPI
    MPI_Finalize();

    return 0;
}