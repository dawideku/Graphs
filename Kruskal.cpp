#include "Kruskal.h"
#include <algorithm>
#include <numeric>

class DisjointSet {
    std::vector<int> parent; //tablica zawierajaca rodzicow
public:
    DisjointSet(int n) : parent(n) {//inicjalizacja kazdego elementu
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) { //znajdowanie rodzicow w zbiorze
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int u, int v) { //przypisywanie rodzicow do odpowiednich elementow
        parent[find(u)] = find(v);
    }

    bool same(int u, int v) { //sprawdzenie czy dwa elementy nie sa takie same
        return find(u) == find(v);
    }
};

std::vector<std::pair<std::pair<int, int>, int>> Kruskal::execute(const std::vector<std::vector<std::pair<int, int>>>& adjacencyList) {
    std::vector<std::pair<std::pair<int, int>, int>> result;
    int n = adjacencyList.size();
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    //konwersja listy
    for (int u = 0; u < n; ++u) {
        for (const auto& edge : adjacencyList[u]) {
            int v = edge.first;
            int weight = edge.second;
            edges.emplace_back(weight, std::make_pair(u, v));
        }
    }
    //sortowanie krawedzi
    std::sort(edges.begin(), edges.end());

    DisjointSet ds(n);
    //przetwarzanie kolejnych krawedzi
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int weight = edge.first;
        if (!ds.same(u, v)) {
            result.emplace_back(std::make_pair(u, v), weight);
            ds.merge(u, v);
        }
    }
    return result;
}
