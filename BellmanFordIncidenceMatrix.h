#ifndef BELLMANFORDINCIDENCEMATRIX_H
#define BELLMANFORDINCIDENCEMATRIX_H

#include <vector>

class BellmanFordIncidenceMatrix {
public:
    static std::vector<int> shortestPath(int startVertex, const std::vector<std::vector<int>>& incidenceMatrix, const std::vector<int>& edgeWeights);
};

#endif // BELLMANFORDINCIDENCEMATRIX_H
