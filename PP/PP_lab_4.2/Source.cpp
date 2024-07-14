#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <numeric> 
#include <vector>
#include <random>
#include <mpi.h>

using namespace std;
using namespace chrono;
using graph_t = vector<vector<size_t>>;

istream& operator>>(istream& is, graph_t& graph) {
    size_t n;   is >> n; // вершины
    size_t m;   is >> m; // ребра
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

size_t colorize(const graph_t& graph, const vector<size_t>& order, int test_num) {
    if (test_num == 9) {
        cout << "colorize\n";
    }
    size_t size = graph.size();
    vector<size_t> colored(size, 0);     // закрашенные вершины
    vector<size_t> colors(size, 0);      // цвета вершин
    vector<size_t> used_colors(size, 0); // использованные цвета

    //for (size_t v : order) {
    if (test_num == 9) {
        printf("graph size: %d\n", size);
        printf("graph[0] size: %d\n", graph[0].size());
    }
        for (int i = 0; i < graph[0].size(); ++i) {

            size_t to = graph[0][i];
            if (to < size) {
                if (colored[to] == 1) {
                    used_colors[colors[to]] = 1; // этот цвет занят
                }
            }
            else {
                if (test_num == 9) {
                    printf("%d ", to);
                }
            }
        }
        size_t c = _mex(used_colors); // ищем незанятый цвет
        colored[0] = 1;               // помечаем вершину как раскрашенную
        colors[0] = c;                // раскрашиваем вершину
        used_colors.assign(size, 0);  // сброс всех цветов
    //}

    return 1 + *max_element(colors.begin(), colors.end());
}

size_t MPIColorize(const graph_t& graph, int world_rank, int world_size, int test_num) {
    if (test_num == 9) {
        cout << "mpicolorize\n";
    }
    size_t size = graph.size();
    size_t orders_count = 500;
    vector<size_t> order(size);
    iota(order.begin(), order.end(), 0);    //Задаем прямой порядок вершин

    random_device rd;
    mt19937 g(rd());
    size_t chunk_size = orders_count / world_size;
    size_t local_min = size;

    //for (size_t i = 0; i < chunk_size; ++i) {
        shuffle(order.begin(), order.end(), g);
        local_min = min(local_min, colorize(graph, order, test_num));
    //}

    size_t global_min;
    MPI_Reduce(&local_min, &global_min, 1, MPI_UNSIGNED_LONG, MPI_MIN, 0, MPI_COMM_WORLD); //Среди всех минимумов находим мин и отправляем в поток 0 в global_min

    return global_min;
}

void broadcast_graph(graph_t& graph, int world_rank, int test_num) {
    if (test_num == 9) {
        cout << "broadcast_graph\n";
    }
    size_t n, m;                                    // n - кол-во вершин, m - кол-во граней
    if (world_rank == 0) {                          // Задача главного процесса 0
        n = graph.size();
        m = 0;
        for (const vector<size_t>& neighbors : graph) {
            m += neighbors.size();
        }
    }

    MPI_Bcast(&n, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD); // Процесс 0 передает n всем остальным процессам
    MPI_Bcast(&m, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD); // Процесс 0 передает m всем остальным процессам

    if (test_num == 9) {
        printf("n: %d\n", n);
        printf("m: %d\n", m);
    }

    if (world_rank != 0) {  // Задача подчиненных процессов
        graph.resize(n);    // Задаем графу размер кол-во вершин
    }

    vector<size_t> edges;
    if (world_rank == 0) {                  // Задача главного процесса 0
        for (size_t i = 0; i < n; ++i) {    // Считываем все грани из графа
            for (size_t j : graph[i]) {
                edges.push_back(i);
                edges.push_back(j);
            }
        }
    }
    else {
        edges.resize(2 * m);
    }

    if (test_num == 9) {
        printf("edges size: %d\n", edges.size());
    }

    MPI_Bcast(edges.data(), edges.size(), MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD); // Процесс 0 передает массив граней всем процессам

    if (world_rank != 0) {                            // Задача подчиненных процессов
        for (size_t i = 0; i < m; ++i) {    // Загружаем грани в граф
            size_t a = edges[2 * i];
            size_t b = edges[2 * i + 1];
            graph[a].push_back(b);
        }
    }

    return;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);                     /* Инициализируем библиотеку */

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); /* Процесс узнает количество задач в запущенном приложении */
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); /* Процесс узнает свой номер: от 0 до (size-1) */

    graph_t graph;
    size_t cnt = 0;
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (world_rank == 0) {                      // Задача главного процесса 0
        input >> cnt;                           // Получаем из input кол-во тестовых графов
        output << cnt << endl;                  // Выводим в output кол-во тестовых графов
    }

    MPI_Bcast(&cnt, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD); // Процесс 0 передает значение cnt всем остальным процессам

    for (size_t i = 0; i < 10; ++i) {

        if (world_rank == 0) {                  // Задача главного процесса 0
            input >> graph;                     // Получаем из input граф
        }

        broadcast_graph(graph, world_rank, i);     // Процесс 0 передает граф всем остальным процессам

        auto start = system_clock::now();
        size_t res = MPIColorize(graph, world_rank, world_size, i);
        auto stop = system_clock::now();

        //if (world_rank == 0) {                  // Задача главного процесса 0
            auto time = duration_cast<milliseconds>(stop - start).count();
            ofstream output("output.txt", ios::app);
            output << res << endl;
            if (i == 9) {
                cout << "rank: " << world_rank << " number: " << i << endl;
            }
        //}
    }

    MPI_Finalize();                             /* Все задачи завершают выполнение */
    return 0;
}