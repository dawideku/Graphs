#include "Dijkstra.h"
#include <queue>
#include <vector>
#include <utility>
#include <limits>

using namespace std;

vector<int> Dijkstra::shortestPath(int startVertex, const vector<vector<pair<int, int>>>& adjacencyList) {
    int n = adjacencyList.size(); //inicjalizacja tablicy odleglosci, na poczatku nieskonczonosc
    vector<int> distances(n, numeric_limits<int>::max());
    distances[startVertex] = 0; //odleglosc od startowego wierzcholka

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        int currentDistance = pq.top().first; //aktualna odleglosc oraz wierzcholek
        int currentVertex = pq.top().second;
        pq.pop();

        if (currentDistance > distances[currentVertex]) continue;
        //przetwarzanie sasiadow
        for (const auto& neighbor : adjacencyList[currentVertex]) {
            int nextVertex = neighbor.first;
            int weight = neighbor.second;
            int distance = currentDistance + weight;
            //aktualizacja odleglosci
            if (distance < distances[nextVertex]) {
                distances[nextVertex] = distance;
                pq.push({distance, nextVertex});
            }
        }
    }

    return distances;
}
