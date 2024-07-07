#include <vector>
#include <iostream>
#include <cstdint>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

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

size_t colorize(const graph_t& graph) {
    size_t size = graph.size();
    vector<size_t> order(size);
    size_t orders_count = 500;
    vector<vector<size_t>> orders(orders_count);

    for (size_t i = 0; i < size; ++i) {
        order[i] = i;
    }

    for (auto& ord : orders) {
        random_shuffle(order.begin(), order.end());
        ord = order;
    }

    size_t min = graph.size();
    for (const auto& ord : orders) {
        vector<size_t> colored(size, 0);
        vector<size_t> colors(size, 0);
        vector<size_t> used_colors(size, 0);

        for (size_t v : ord) {
            for (auto to : graph[v]) {
                if (colored[to]) {
                    used_colors[colors[to]] = 1; //этот цвет занят
                }
            }
            auto c = _mex(used_colors);  //ищем незанятый цвет
            colored[v] = 1;              //помечаем вершину как раскрашеную
            colors[v] = c;               //раскрашиваем вершину
            used_colors.assign(size, 0); //сброс всех цветов
        }
        size_t colors_count = 1 + *max_element(colors.begin(), colors.end());
        min = std::min(min, colors_count);
    }

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

        auto res = colorize(graph);

        auto stop = chrono::system_clock::now();

        auto time = duration_cast<milliseconds>(stop - start).count();

        output << res << endl;
        cout << time << endl;
    }

    return 0;
}


