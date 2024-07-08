#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>
#include <numeric> 

using namespace std;
using namespace chrono;
using graph_t = vector<vector<size_t>>;

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

size_t _mex(const vector<size_t>& set) {
    return static_cast<size_t>(find(set.begin(), set.end(), 0) - set.begin());
}

size_t LineColorize(const graph_t& graph) {
    size_t size = graph.size();
    vector<size_t> order(size);
    size_t orders_count = 500;
    vector<vector<size_t>> orders(orders_count);

    /*for (size_t i = 0; i < size; ++i) {                //O(size)
        order[i] = i;
    }*/

    iota(order.begin(), order.end(), 0);

    for (auto& ord : orders) {                         //O(orders_count)
        random_shuffle(order.begin(), order.end());
        ord = order;
    }

    size_t min = graph.size();
    for (const auto& ord : orders) {                   //O(orders_count)
        vector<size_t> colored(size, 0);     //закрашеные вершины
        vector<size_t> colors(size, 0);      //цвета вершин
        vector<size_t> used_colors(size, 0); //использованые цвета

        for (size_t v : ord) {                         //O(size)
            for (auto to : graph[v]) {                 //O(size)
                if (colored[to]) {
                    used_colors[colors[to]] = 1; //этот цвет занят
                }
            }
            size_t c = _mex(used_colors);//ищем незанятый цвет
            colored[v] = 1;              //помечаем вершину как раскрашеную
            colors[v] = c;               //раскрашиваем вершину
            used_colors.assign(size, 0); //сброс всех цветов
        }
        size_t colors_count = 1 + *max_element(colors.begin(), colors.end());
        min = std::min(min, colors_count);
    }

    return min; //O(size + orders_count + orders_count * (size * size)) = O(orders_count * size^2)
}

size_t colorize_chunk(const graph_t& graph, const vector<vector<size_t>>& orders, size_t start, size_t end) {
    size_t min = graph.size();
    size_t size = graph.size();

    for (size_t i = start; i < end; ++i) {
        const auto& ord = orders[i];
        vector<size_t> colored(size, 0);
        vector<size_t> colors(size, 0);
        vector<size_t> used_colors(size, 0);

        for (size_t v : ord) {
            for (auto to : graph[v]) {
                if (colored[to]) {
                    used_colors[colors[to]] = 1;
                }
            }
            size_t c = _mex(used_colors);
            colored[v] = 1;
            colors[v] = c;
            used_colors.assign(size, 0);
        }
        size_t colors_count = 1 + *max_element(colors.begin(), colors.end());
        min = std::min(min, colors_count);
    }

    return min;
}

size_t ParallelColorize(const graph_t& graph) {
    size_t size = graph.size();
    vector<size_t> order(size);
    size_t orders_count = 500;
    vector<vector<size_t>> orders(orders_count);

    iota(order.begin(), order.end(), 0);

    for (auto& ord : orders) {
        random_shuffle(order.begin(), order.end());
        ord = order;
    }

    size_t min = graph.size();
    size_t num_threads = 4;
    vector<thread> threads;
    vector<size_t> mins(num_threads, graph.size());

    size_t chunk_size = orders_count / num_threads;                             //опр размер подзадачи

    for (size_t t = 0; t < num_threads; ++t) {                                  //цикл запуска потоков
        size_t start = t * chunk_size;
        size_t end = start + chunk_size; //size_t end = (t == num_threads - 1) ? orders_count : start + chunk_size;
        threads.emplace_back([&graph, &orders, &mins, t, start, end]() {        //запуск потока
            mins[t] = colorize_chunk(graph, orders, start, end);                //функция потока
        });
    }

    for (auto& thread : threads) {                                              //ожидаем завершения всех потоков
        thread.join();
    }

    min = *min_element(mins.begin(), mins.end());

    return min;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    graph_t graph;
    size_t cnt;
    input >> cnt;
    output << cnt << endl;
    for (size_t i = 0; i < cnt; ++i) {
        input >> graph;
        auto start = chrono::system_clock::now();

        auto res = LineColorize(graph);

        auto stop = chrono::system_clock::now();

        auto time = duration_cast<milliseconds>(stop - start).count();

        output << res << endl;
        cout << time << endl;
    }

    input.seekg(0, ios::beg);
    input >> cnt;
    for (size_t i = 0; i < cnt; ++i) {
        input >> graph;
        auto start = chrono::system_clock::now();

        auto res = ParallelColorize(graph);

        auto stop = chrono::system_clock::now();

        auto time = duration_cast<milliseconds>(stop - start).count();

        output << res << endl;
        cout << time << endl;
    }

    return 0;
}
