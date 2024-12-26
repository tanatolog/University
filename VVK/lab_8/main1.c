#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define generate_random_string(str, len) for(int i = 0; i < len; i++) str[i] = 'A' + rand() % 26



// Хеш-функция Рабина-Карпа
unsigned long long compute_hash(const char *str, int len, int base, int mod) {
    unsigned long long hash = 0;
    for (int i = 0; i < len; i++) {
        hash = (hash * base + str[i]) % mod;
    }
    return hash;
}

// Функция Рабина-Карпа для поиска
int rabin_karp(const char *text, int text_len, const char *pattern, int pattern_len, int base, int mod) {
    int match_count = 0;
    unsigned long long pattern_hash = compute_hash(pattern, pattern_len, base, mod);
    unsigned long long current_hash = compute_hash(text, pattern_len, base, mod);

    for (int i = 0; i <= text_len - pattern_len; i++) {
        if (current_hash == pattern_hash && strncmp(text + i, pattern, pattern_len) == 0) {
            match_count++;
        }
        if (i < text_len - pattern_len) {
            current_hash = (current_hash * base - text[i] * (unsigned long long)pow(base, pattern_len) % mod + text[i + pattern_len]) % mod;
            if (current_hash < 0) current_hash += mod;
        }
    }
    return match_count;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int test_runs = 3;
    /* if (rank == 0) {
        printf("Enter the number of test runs: ");
        fflush(stdout);
        scanf("%d", &test_runs);
    } */

    MPI_Bcast(&test_runs, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char *pattern = "ABC";
    int pattern_len = strlen(pattern);
    int base = 256, mod = 101;

    //int text_lengths[] = {10000000, 20000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000, 90000000, 100000000, 110000000, 120000000, 130000000, 140000000, 150000000, 160000000};
    //x2
    int text_lengths[] = {20000000, 40000000, 60000000, 80000000, 100000000, 120000000, 140000000, 160000000, 180000000, 200000000, 220000000, 240000000, 260000000, 280000000, 300000000, 320000000};

    int num_lengths = sizeof(text_lengths) / sizeof(text_lengths[0]);

    for (int i = 0; i < num_lengths; i++) {
        int text_len = text_lengths[i];
        char *text = NULL;

        if (rank == 0) {
            text = (char *)malloc((text_len + 1) * sizeof(char));
            srand(time(NULL));
            generate_random_string(text, text_len);
            text[text_len] = '\0';
        }

        if (rank != 0) {
            text = (char *)malloc((text_len + 1) * sizeof(char));
        }
        MPI_Bcast(text, text_len + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

        // Расчет времени выполнения
        double total_time = 0.0;

        // Бежим test_runs раз по циклу
        for (int t = 0; t < test_runs; t++) {
            double start_time = MPI_Wtime();

            // Делим текст между процессами
            int local_len = text_len / size;
            int extra = text_len % size;

            int start = rank * local_len + (rank < extra ? rank : extra);
            int end = start + local_len + (rank < extra ? 1 : 0);

            // Выполнение алгоритма Рабина-Карпа
            int local_count = rabin_karp(text + start, end - start, pattern, pattern_len, base, mod);

            // Сбор результатов всех процессов
            int global_count = 0;
            MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

            double end_time = MPI_Wtime();
            double elapsed_time = end_time - start_time;

            if (rank == 0) {
                total_time += elapsed_time;
            }
        }

        // Вывод среднего времени только на процессе 0
        if (rank == 0) {
            printf("Text length: %d, Average time for %d test runs: %f seconds\n", text_len, test_runs, total_time / test_runs);
        }

        free(text);
    }

    MPI_Finalize();
    return 0;
}
