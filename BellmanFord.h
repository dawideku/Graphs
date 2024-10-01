#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <vector>
#include <utility>

class BellmanFord {
public:
    static std::vector<int> shortestPath(int startVertex, const std::vector<std::vector<std::pair<int, int>>>& adjacencyList);
};

#endif // BELLMANFORD_H
