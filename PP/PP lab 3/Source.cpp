#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <numeric> 
#include <vector>
#include <omp.h>
#include <random>

#include <thread>

using namespace std;
using namespace chrono;
using graph_t = vector<vector<size_t>>;

istream& operator>>(istream& is, graph_t& graph) {
    size_t n;   is >> n; // vertexes
    size_t m;   is >> m; // edges
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

size_t OMPColorize(const graph_t& graph) {
    size_t size = graph.size();
    size_t orders_count = 500;
    vector<vector<size_t>> orders(orders_count);

#pragma omp parallel for                           //выполняем цикл параллельно
    for (int i = 0; i < orders_count; ++i) {
        random_device rd;
        mt19937 g(rd());
        vector<size_t> order(size);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), g);
        orders[i] = order;
    }

    vector<size_t> storage(orders_count, size);

#pragma omp parallel for schedule(guided)
    for (int i = 0; i < orders_count; ++i) {                   
        vector<size_t> colored(size, 0);     //закрашеные вершины
        vector<size_t> colors(size, 0);      //цвета вершин
        vector<size_t> used_colors(size, 0); //использованые цвета
        vector<size_t> ord = orders[i];      //текущий порядок

        for (size_t v : ord) {                         
            for (auto to : graph[v]) {               
                if (colored[to]) {
                    used_colors[colors[to]] = 1; //этот цвет занят
                }
            }
            size_t c = _mex(used_colors);//ищем незанятый цвет
            colored[v] = 1;              //помечаем вершину как раскрашеную
            colors[v] = c;               //раскрашиваем вершину
            used_colors.assign(size, 0); //сброс всех цветов
        }
        storage[i] = 1 + *max_element(colors.begin(), colors.end());
    }

    size_t min = *min_element(storage.begin(), storage.end());
    return min;
}

int main(int argc, char* argv[]) {
    ifstream input("input.txt");
    ofstream output("output.txt");

    graph_t graph;
    size_t cnt;
    input >> cnt;
    output << cnt << endl;
    for (size_t i = 0; i < cnt; ++i) {
        input >> graph;
        auto start = system_clock::now();

        auto res = OMPColorize(graph);

        auto stop = system_clock::now();

        auto time = duration_cast<milliseconds>(stop - start).count();

        output << res << endl;
        cout << time << endl;
    }
    return 0;
}