#ifndef KRUSKAL_INCIDENCE_MATRIX_H
#define KRUSKAL_INCIDENCE_MATRIX_H

#include <vector>
#include <algorithm>
#include <numeric>

class DisjointSet {
    std::vector<int> parent;
public:
    DisjointSet(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int u, int v) {
        parent[find(u)] = find(v);
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

class KruskalIncidenceMatrix {
public:
    static std::vector<std::pair<std::pair<int, int>, int>> execute(const std::vector<std::vector<int>>& incidenceMatrix, const std::vector<int>& edgeWeights) {
        std::vector<std::pair<std::pair<int, int>, int>> result;
        int n = incidenceMatrix.size();
        int m = incidenceMatrix[0].size();
        std::vector<std::pair<int, std::pair<int, int>>> edges;

        for (int j = 0; j < m; ++j) {
            int u = -1, v = -1;
            for (int i = 0; i < n; ++i) {
                if (incidenceMatrix[i][j] > 0)
                    u = i;
                else if (incidenceMatrix[i][j] < 0)
                    v = i;
            }
            if (u != -1 && v != -1) {
                edges.emplace_back(edgeWeights[j], std::make_pair(u, v));
            }
        }
        std::sort(edges.begin(), edges.end());

        DisjointSet ds(n);
        for (const auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int weight = edge.first;
            if (!ds.same(u, v)) {
                result.emplace_back(std::make_pair(u, v), weight);
                ds.merge(u, v);
            }
        }
        return result;
    }
};

#endif // KRUSKAL_INCIDENCE_MATRIX_H