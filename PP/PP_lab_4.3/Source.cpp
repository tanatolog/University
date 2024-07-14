#include <vector>
#include <random>
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>

using namespace std;
using graph_t = vector<vector<size_t>>;

const int MASTER_RANK = 0;

istream& operator>>(istream& is, graph_t& graph) {
    size_t n; is >> n; // vertexes
    size_t m; is >> m; // edges
    graph.clear();
    graph.resize(n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b; 
        is >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    return is;
}

inline size_t _mex(const vector<size_t>& set) {
    return static_cast<size_t>(find(set.begin(), set.end(), 0) - set.begin());
}

size_t colorize(const graph_t& graph, const vector<size_t>& order) {
    size_t size = graph.size();

    vector<size_t> colored(size, 0);
    vector<size_t> colors(size, 0);
    vector<size_t> used_colors(size, 0);

    for (size_t v : order) {
        if (!colored[v]) {
            for (auto to : graph[v]) {
                if (colored[to]) {
                    used_colors[colors[to]] = 1;
                }
            }
            colored[v] = 1;

            auto color = _mex(used_colors);
            colors[v] = color;
            used_colors.assign(size, 0);
        }
    }

    return 1 + *max_element(colors.begin(), colors.end());
}

size_t TaskForSlave(const graph_t& graph, size_t task_count) {
    vector<size_t> order(graph.size());
    iota(order.begin(), order.end(), 0);                    //Задаем прямой порядок вершин

    vector<vector<size_t>> perms(task_count);

    mt19937 g(static_cast<unsigned int>(time(nullptr)));
    for (size_t i = 0; i < task_count; ++i) {
        shuffle(order.begin(), order.end(), g);
        perms[i] = order;
    }

    vector<size_t> results(task_count, graph.size());

    for (size_t i = 0; i < task_count; i++) {
        results[i] = colorize(graph, perms[i]);             //Покраска графа
    }

    return *min_element(results.begin(), results.end());
}

void slave_routine(int wr, int ws) {
    size_t chunk = 500u / (ws - 1);                         //определяем объем работы подчиненного
    ifstream input("input.txt");

    graph_t graph;
    size_t cnt;
    input >> cnt;                                           //получаем из input кол-во тестов

    for (size_t i = 0; i < cnt; ++i) {
        input >> graph;

        auto start = MPI_Wtime() * 1000.0;                  //начало отсчета

        size_t result = TaskForSlave(graph, chunk);         //выполнение задачи

        auto stop = MPI_Wtime() * 1000.0;                   //конец отсчета
        auto time = static_cast<size_t>(stop - start);      //вычисление времени выполнения задачи

        size_t buffer[2] = { time, result };

        MPI_Send(&buffer, 2, MPI_UNSIGNED_LONG, MASTER_RANK, static_cast<int>(i), MPI_COMM_WORLD); //Отправка результата в главный процесс
    }
}

void master_routine(int ws) {
    ifstream input("input.txt");
    ofstream output("output.txt");

    size_t cnt;
    input >> cnt;               // Получаем из input кол-во тестовых графов
    output << cnt << endl;      // Выводим в output кол-во тестовых графов

    vector<size_t> results(cnt, numeric_limits<size_t>::max()); //вектор результатов тестов
    vector<size_t> times(cnt, 0);                               //вектор времени тестов

    for (size_t i = 0; i < cnt; ++i) {
        size_t rank_res[2];                                     //отдельный результат подчиненного потока

        for (int rank = 1; rank < ws; ++rank) {
            MPI_Recv(&rank_res, 2, MPI_UNSIGNED_LONG, rank, static_cast<int>(i), MPI_COMM_WORLD, MPI_STATUS_IGNORE); //ждем когда подчиненные отработают, и получаем их результат
            size_t time = rank_res[0];                          
            size_t res = rank_res[1];
            results[i] = std::min(results[i], res);             //запись результата
            times[i] += time;                                   //сумма времени работы всех подчиненных?
        }

        output << setw(4) << results[i] << endl;                //вывод в файл результата теста
        cout << times[i] / (ws - 1) << endl;                    //вывод в консоль времени теста
    }

}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);                         /* Инициализируем библиотеку */

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);     /* Процесс узнает свой номер: от 0 до (size-1) */
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);     /* Процесс узнает количество задач в запущенном приложении */

    if (world_rank == 0) {
        master_routine(world_size);                 // Задача главного процесса 0
    }
    else {
        slave_routine(world_rank, world_size);      // Задача подчиненных процессов
    }

    MPI_Finalize();                                 /* Все процессы завершают выполнение */
}