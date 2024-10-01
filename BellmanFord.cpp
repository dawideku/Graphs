#include "BellmanFord.h"
#include <vector>
#include <utility>
#include <limits>
#include <iostream>

using namespace std;

vector<int> BellmanFord::shortestPath(int startVertex, const vector<vector<pair<int, int>>>& adjacencyList) {
    int n = adjacencyList.size();
    vector<int> distances(n, numeric_limits<int>::max()); //tablica odleglosci, poczatkowo nieskonczonosc
    distances[startVertex] = 0;     //odleglosc od startowego wierzcholka ustawiana na 0

    //relaksacja krawedzi n-1 razy
    for (int i = 1; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            //przetwarzanie sasiadow
            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                //relaksacja
                if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }
    }

    return distances;
}
