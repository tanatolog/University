#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int size, rank, i;
    MPI_Init(&argc, &argv);                 /* Инициализируем библиотеку */
    MPI_Comm_size(MPI_COMM_WORLD, &size);   /* Узнаем количество задач в запущенном приложении */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* ... и свой собственный номер: от 0 до (size-1) */

    /* задача с номером 0 сообщает пользователю размер группы,
       к которой прикреплена область связи,
       с описателем (коммуникатором) MPI_COMM_WORLD,
       т.е. число процессов в приложении!!*/
    if (rank == 0)
        printf("Total processes count = %d\n", size);
    fflush(stdout);  /* Очищаем буфер вывода */

    printf("Hello! My rank in MPI_COMM_WORLD = %d\n", rank);  /* Каждая задача выводит пользователю свой номер */
    fflush(stdout);  /* Очищаем буфер вывода */

    MPI_Barrier(MPI_COMM_WORLD);  /* Точка синхронизации */

    /* Задача 0 печатает аргументы командной строки.
       В командной строке могут быть параметры,
       добавляемые загрузчиком MPIRUN.*/
    if (rank == 0) {
        printf("Command line of process 0: ");
        for (i = 0; i < argc; i++)
            printf("%d: \"%s\"\n", i, argv[i]);
        fflush(stdout);  /* Очищаем буфер вывода */
    }

    MPI_Finalize();  /* Все задачи завершают выполнение */
    return 0;
}