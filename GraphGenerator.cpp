#include "GraphGenerator.h"
#include <random>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

GraphGenerator::GraphGenerator(int n, int density)
        : n(n), density(density), maxEdges(n * (n - 1) / 2), numEdges((maxEdges * density) / 100) {}

void GraphGenerator::generateEdges() {
    //inicjalizacja generatorow liczb pseudo-losowych
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);
    uniform_int_distribution<> vertexDistrib(0, n - 1);

    //generowanie wag
    edgeWeights.resize(numEdges);
    for (int i = 0; i < numEdges; i++) {
        edgeWeights[i] = distrib(gen);
    }

    //wygenerowanie MST
    for (int i = 0; i < n - 1; i++) {
        addEdge(i, i + 1, edgeWeights[i]);
    }

    //dodanie pozostalych wierzcholkow
    while (edges.size() < numEdges) {
        int v1 = vertexDistrib(gen);
        int v2 = vertexDistrib(gen);
        if (v1 != v2 && edges.find({min(v1, v2), max(v1, v2)}) == edges.end()) {
            addEdge(v1, v2, edgeWeights[edges.size()]);
        }
    }
}

const vector<GraphGenerator::Edge>& GraphGenerator::getEdges() const {
    return edgeList;
}

const vector<int>& GraphGenerator::getEdgeWeights() const {
    return edgeWeights;
}

void GraphGenerator::setEdges(const vector<Edge>& edges) {
    edgeList = edges;
    this->edges.clear();
    for (const auto& edge : edges) {
        this->edges.insert({min(edge.v1, edge.v2), max(edge.v1, edge.v2)});
    }
}

void GraphGenerator::setEdgeWeights(const vector<int>& weights) {
    edgeWeights = weights;
}

void GraphGenerator::addEdge(int v1, int v2, int weight) {
    edges.insert({min(v1, v2), max(v1, v2)});
    edgeList.push_back({v1, v2});
}
