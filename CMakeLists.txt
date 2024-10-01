cmake_minimum_required(VERSION 3.28)
project(AIZO_GRAFY)

set(CMAKE_CXX_STANDARD 17)

add_executable(AIZO_GRAFY main.cpp
        GraphGenerator.cpp
        GraphGenerator.h
        IncidenceMatrix.cpp
        IncidenceMatrix.h
        AdjacencyList.cpp
        AdjacencyList.h
        Dijkstra.cpp
        Dijkstra.h
        DijkstraIncidenceMatrix.cpp
        DijkstraIncidenceMatrix.h
        Kruskal.cpp
        Kruskal.h
        KruskalIncidenceMatrix.cpp
        KruskalIncidenceMatrix.h
        BellmanFord.cpp
        BellmanFord.h
        BellmanFordIncidenceMatrix.cpp
        BellmanFordIncidenceMatrix.h
)
