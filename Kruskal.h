#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <utility>

class Kruskal {
public:
    static std::vector<std::pair<std::pair<int, int>, int>> execute(const std::vector<std::vector<std::pair<int, int>>>& adjacencyList);
};

#endif
