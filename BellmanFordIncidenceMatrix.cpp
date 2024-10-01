#include "BellmanFordIncidenceMatrix.h"
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

vector<int> BellmanFordIncidenceMatrix::shortestPath(int startVertex, const vector<vector<int>>& incidenceMatrix, const vector<int>& edgeWeights) {
    int n = incidenceMatrix.size(); // Liczba wierzchołków
    int m = incidenceMatrix[0].size(); // Liczba krawędzi
    vector<int> distances(n, numeric_limits<int>::max());
    distances[startVertex] = 0;

    // relaksacja krawedzi
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = -1, v = -1;
            for (int k = 0; k < n; ++k) {
                if (incidenceMatrix[k][j] > 0) {
                    u = k;
                } else if (incidenceMatrix[k][j] < 0) {
                    v = k;
                }
            }
            if (u != -1 && v != -1 && distances[u] != numeric_limits<int>::max() && distances[u] + edgeWeights[j] < distances[v]) {
                distances[v] = distances[u] + edgeWeights[j];
            }
        }
    }

    return distances;
}
