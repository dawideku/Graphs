#include "DijkstraIncidenceMatrix.h"
#include <vector>
#include <limits>
#include <queue>
#include <utility>
#include <iostream>

using namespace std;

vector<int> DijkstraIncidenceMatrix::shortestPath(int startVertex, const vector<vector<int>>& incidenceMatrix, const vector<int>& edgeWeights) {
    int n = incidenceMatrix.size(); //liczba krawedzi i wierzcholkow
    int m = incidenceMatrix[0].size();
    vector<int> distances(n, numeric_limits<int>::max());
    distances[startVertex] = 0;

    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distances[u]) continue;
        //przetwarzanie sasiadow wierzcholka
        for (int j = 0; j < m; ++j) {
            if (incidenceMatrix[u][j] > 0) { //szukanie wierzcholka startowego
                int weight = edgeWeights[j];
                int v = -1;

                for (int i = 0; i < n; ++i) {
                    if (incidenceMatrix[i][j] < 0) { //szuaknie wierzcholka docelowego
                        v = i;
                        break;
                    }
                }
                //aktualizacja odleglosci
                if (v != -1 && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.push({distances[v], v});
                }
            }
        }
    }

    return distances;
}
