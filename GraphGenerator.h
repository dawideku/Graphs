#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <vector>
#include <set>
#include <utility>

using namespace std;

class GraphGenerator {
public:
    struct Edge {
        int v1;
        int v2;
    };

    GraphGenerator(int n, int density);
    void generateEdges();
    const vector<Edge>& getEdges() const;
    const vector<int>& getEdgeWeights() const;

    void setEdges(const vector<Edge>& edges);
    void setEdgeWeights(const vector<int>& weights);

protected:
    int n; // liczba wierzchołków
    int density; // gęstość grafu w %
    int maxEdges;
    int numEdges;
    vector<Edge> edgeList;
    vector<int> edgeWeights;
    set<pair<int, int>> edges;

private:
    void addEdge(int v1, int v2, int weight);
};

#endif // GRAPHGENERATOR_H
