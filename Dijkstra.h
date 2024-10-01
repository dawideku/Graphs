#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <utility>
#include <limits>

class Dijkstra {
public:
    static std::vector<int> shortestPath(int startVertex, const std::vector<std::vector<std::pair<int, int>>>& adjacencyList);
};

#endif // DIJKSTRA_H
