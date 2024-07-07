#include <fstream>
#include <random>
#include <set>
#include <algorithm>

using namespace std;

int randrange(int a, int b) {
    static default_random_engine engine;

    uniform_int_distribution<int> dist(a, b - 1);

    return dist(engine);
}

void generate(ostream& output, int vert_count, int edges_count) {
    set<pair<int, int>> edges;
    while (edges.size() < edges_count) {
        int a = randrange(0, vert_count);
        int b = randrange(0, vert_count);
        if (a != b) {
            edges.insert(minmax(a, b));
        }
    }

    output << vert_count << ' ' << edges_count << endl;
    for (const auto& edge : edges) {
        output << edge.first << ' ' << edge.second << endl;
    }
}

int main() {
    ofstream output("../input.txt");

    pair<int, int> params[] = {
            {5, 7},
            {75, 1000},
            {75, 2500}, {90, 300}, {95, 2500}, {150, 6500},
            {170, 10000}, {250, 14000}, {250, 17000}, {300, 34000}, 
            {400, 40000}
    };

    constexpr size_t cases_count = size(params);

    output << cases_count << endl;
    for (int i = 0; i < cases_count; ++i) {
        generate(output, params[i].first, params[i].second);
        output << endl;
    }

    return 0;
}