#ifndef DIJKSTRAINCIDENCEMATRIX_H
#define DIJKSTRAINCIDENCEMATRIX_H

#include <vector>
#include <utility>

class DijkstraIncidenceMatrix {
public:
    static std::vector<int> shortestPath(int startVertex, const std::vector<std::vector<int>>& incidenceMatrix, const std::vector<int>& edgeWeights);
};

#endif // DIJKSTRAINCIDENCEMATRIX_H
