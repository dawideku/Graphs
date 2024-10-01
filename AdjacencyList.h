#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "GraphGenerator.h"
#include <vector>

struct ListNode {
    int vertex;
    int weight;
    ListNode* next;
};

class AdjacencyList : public GraphGenerator {
public:
    AdjacencyList(int n, int density);
    ~AdjacencyList();
    void createList();
    void printList() const;

    void setEdges(const std::vector<Edge>& edges);
    void setEdgeWeights(const std::vector<int>& weights);

    const std::vector<std::vector<std::pair<int, int>>>& getAdjList() const; // Getter for the adjacency list

private:
    ListNode** adjacencyList;
    std::vector<std::vector<std::pair<int, int>>> adjList; // Store adjacency list in a vector for easier access
};

#endif // ADJACENCYLIST_H