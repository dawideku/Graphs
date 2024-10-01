#ifndef INCIDENCEMATRIX_H
#define INCIDENCEMATRIX_H

#include "GraphGenerator.h"
#include <vector>

class IncidenceMatrix : public GraphGenerator {
public:
    IncidenceMatrix(int n, int density);
    void createMatrix();
    void printMatrix() const;

    void setEdges(const std::vector<Edge>& edges);
    void setEdgeWeights(const std::vector<int>& weights);

    const std::vector<std::vector<int>>& getMatrix() const; // Getter for the matrix

private:
    signed int **A;
    std::vector<std::vector<int>> matrix; // Store matrix in a vector for easier access
};

#endif // INCIDENCEMATRIX_H
