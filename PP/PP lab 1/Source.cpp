#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;
using graph_t = vector<vector<size_t>>;

istream& operator>>(istream& is, graph_t& graph) {
    size_t n;
    size_t m;
    is >> n; // вершины
    is >> m; // грани
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

    for (size_t i = 0; i < size; ++i) {                //O(size)
        order[i] = i;
    }

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

size_t colorize2(const graph_t& graph) {
    size_t size = graph.size();
    vector<size_t> order(size);
    size_t orders_count = 500;
    vector<vector<size_t>> orders(orders_count);

    for (size_t i = 0; i < size; ++i) {                                                                                     //O(size)
        order[i] = i;
    }

    for (auto& ord : orders) {                                                                                              //O(orders_count)
        random_shuffle(order.begin(), order.end());
        ord = order;
    }

    size_t min = graph.size();
    for (const auto& ord : orders) {                                                                                        //O(orders_count)
        vector<int> result(size, -1);         // закрашеные вершины
        vector<bool> available(size, false);  // доступные дли исп цвета

        result[0] = 0;                        // Assign the first color to the first vertex

        for (size_t u : ord) {                // Assign colors to the remaining vertices                                    //O(size)

            for (int adj : graph[u]) {        // Process all adjacent vertices and mark their colors as unavailable         //O(size)
                if (result[adj] != -1) {
                    available[result[adj]] = true;
                }
            }

            int color;
            for (color = 0; color < size; ++color) {  // Find the first available color                                     //O(size)
                if (!available[color]) {
                    break;
                }
            }

            result[u] = color;                        // Assign the found color to the current vertex

            for (int adj : graph[u]) {                // Reset the values back to false for the next iteration              //O(size)
                if (result[adj] != -1) {
                    available[result[adj]] = false;
                }
            }
        }
        size_t colors_count = 1 + *max_element(result.begin(), result.end());
        min = std::min(min, colors_count);
    }

    return min; //O(size + orders_count + orders_count * (size * (size + size + size))) = O(orders_count * 3size^2)
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

    input.seekg(0, ios::beg);
    input >> cnt;
    for (size_t i = 0; i < cnt; ++i) {
        input >> graph;
        auto start = chrono::system_clock::now();

        auto res = colorize2(graph);

        auto stop = chrono::system_clock::now();

        auto time = duration_cast<milliseconds>(stop - start).count();

        output << res << endl;
        cout << time << endl;
    }

    return 0;
}


