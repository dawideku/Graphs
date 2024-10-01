#include "IncidenceMatrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

IncidenceMatrix::IncidenceMatrix(int n, int density) : GraphGenerator(n, density) {
    A = new signed int*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new signed int[numEdges];
        fill(A[i], A[i] + numEdges, 0);
    }
}

void IncidenceMatrix::createMatrix() {
    matrix.resize(n, vector<int>(numEdges, 0)); //zmiana rozmiaru macierzy

    for (int i = 0; i < numEdges; i++) {
        int v1 = edgeList[i].v1;
        int v2 = edgeList[i].v2;
        int weight = edgeWeights[i];
        A[v1][i] = weight;   // wierzcholek startowy
        A[v2][i] = -weight;  // wierzcholek końcowy

        matrix[v1][i] = weight;   // wierzcholek startowy w macierzy
        matrix[v2][i] = -weight;  // wierzcholek końcowy w macierzy
    }
}

void IncidenceMatrix::printMatrix() const {//wyswietlenie macierzy
    cout << endl;
    cout << "     ";
    for (int i = 0; i < numEdges; i++) cout << setw(5) << i;
    cout << endl << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << i;
        for (int j = 0; j < numEdges; j++) cout << setw(5) << A[i][j];
        cout << endl;
    }
    cout << endl;
}

const std::vector<std::vector<int>>& IncidenceMatrix::getMatrix() const {
    return matrix;
}


//ustawienie wierzcholkow oraz wag krawedzi
void IncidenceMatrix::setEdges(const vector<Edge>& edges) {
    edgeList = edges;
    this->edges.clear();
    for (const auto& edge : edges) {
        this->edges.insert({min(edge.v1, edge.v2), max(edge.v1, edge.v2)});
    }
}

void IncidenceMatrix::setEdgeWeights(const vector<int>& weights) {
    edgeWeights = weights;
}
