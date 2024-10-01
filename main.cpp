#include "GraphGenerator.h"
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"
#include "Dijkstra.h"
#include "DijkstraIncidenceMatrix.h"
#include "Kruskal.h"
#include "KruskalIncidenceMatrix.h"
#include "BellmanFord.h"
#include "BellmanFordIncidenceMatrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;

class Main {
public:
    static void run() {
        //deklaracja przydatnych zmiennych
        int n, density;
        vector<GraphGenerator::Edge> edges;
        vector<int> weights;
        vector<vector<int>> incidenceMatrix;
        vector<vector<pair<int, int>>> adjacencyList;
        GraphGenerator* generator = nullptr;

        while (true) {
            int choice;
            cout << "Menu:\n";
            cout << "1. Podaj liczbe wierzcholkow i gestosc grafu\n";
            cout << "2. Inicjalizacja macierzy incydencji\n";
            cout << "3. Inicjalizacja listy sasiedztwa\n";
            cout << "4. Wykonaj algorytm Dijkstry\n";
            cout << "5. Wykonaj algorytm Kruskala\n";
            cout << "6. Wykonaj algorytm Bellmana-Forda\n";
            cout << "7. Symulacja\n";
            cout << "8. Wyjdz\n";
            cout << "Wybierz opcje: ";
            cin >> choice;

            switch (choice) {
                //generowanie listy krawedzi oraz wag
                case 1:
                    cout << "Podaj liczbe wierzcholkow: ";
                    cin >> n;
                    cout << "Podaj gestosc (w %): ";
                    cin >> density;

                    delete generator;
                    generator = new GraphGenerator(n, density);
                    generator->generateEdges();

                    edges = generator->getEdges();
                    weights = generator->getEdgeWeights();
                    break;

                case 2:
                    //przypisanie do zmiennej globalnej obiektu macierzy incydencji
                    if (generator) {
                        IncidenceMatrix matrix(n, density);
                        matrix.setEdges(edges);
                        matrix.setEdgeWeights(weights);
                        matrix.createMatrix();
                        incidenceMatrix = matrix.getMatrix();
                        matrix.printMatrix();
                    } else {
                        cout << "Najpierw podaj liczbe wierzcholkow i gestosc grafu.\n";
                    }
                    break;
                    //przypisanie do zmiennej globalnej obiektu listy sasiedztwa
                case 3:
                    if (generator) {
                        AdjacencyList adjList(n, density);
                        adjList.setEdges(edges);
                        adjList.setEdgeWeights(weights);
                        adjList.createList();
                        adjacencyList = adjList.getAdjList();
                        adjList.printList();
                    } else {
                        cout << "Najpierw podaj liczbe wierzcholkow i gestosc grafu.\n";
                    }
                    break;

                case 4: {
                    bool inSubmenu = true;
                    while (inSubmenu) {
                        int choice_2;
                        cout << "Podmenu Dijkstry:\n";
                        cout << "1. Dijkstra - lista sasiedztwa\n";
                        cout << "2. Dijkstra - macierz incydencji\n";
                        cout << "3. Powrot do menu glownego\n";
                        cout << "Wybierz opcje: ";
                        cin >> choice_2;

                        switch (choice_2) {
                            case 1:
                                if (!adjacencyList.empty()) {
                                    int startVertex;
                                    cout << "Podaj wierzcholek poczatkowy: ";
                                    cin >> startVertex;
                                    //pomiar czasu
                                    auto start = std::chrono::high_resolution_clock::now();
                                    vector<int> distances = Dijkstra::shortestPath(startVertex, adjacencyList);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                            end - start).count();
                                    std::cout << "Czas wykonania: " << duration << " mikrosekund" << std::endl;


                                    cout << "Najkrotsze sciezki od wierzcholka " << startVertex << ":\n";
                                    for (int i = 0; i < distances.size(); ++i) {
                                        cout << "Do wierzcholka " << i << ": ";
                                        if (distances[i] == numeric_limits<int>::max()) {
                                            cout << "brak sciezki\n";
                                        } else {
                                            cout << distances[i] << endl;
                                        }
                                    }
                                } else {
                                    cout << "Najpierw zainicjuj reprezentacje.\n";
                                }
                                break;

                            case 2:
                                if (!incidenceMatrix.empty()) {
                                    int startVertex;
                                    cout << "Podaj wierzcholek poczatkowy: ";
                                    cin >> startVertex;

                                    auto start = std::chrono::high_resolution_clock::now();
                                    vector<int> distances = DijkstraIncidenceMatrix::shortestPath(startVertex,
                                                                                                  incidenceMatrix,
                                                                                                  weights);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                            end - start).count();
                                    std::cout << "Czas wykonania: " << duration << " mikrosekund" << std::endl;


                                    cout << "Najkrotsze sciezki od wierzcholka " << startVertex << ":\n";
                                    for (int i = 0; i < distances.size(); ++i) {
                                        cout << "Do wierzcholka " << i << ": ";
                                        if (distances[i] == numeric_limits<int>::max()) {
                                            cout << "brak sciezki\n";
                                        } else {
                                            cout << distances[i] << endl;
                                        }
                                    }
                                } else {
                                    cout << "Najpierw zainicjuj reprezentacje.\n";
                                }
                                break;

                            case 3:
                                inSubmenu = false;
                                break;

                            default:
                                cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                        }
                    }
                    break;
                }
                case 5: {
                    bool inSubmenu = true;
                    while (inSubmenu) {
                        int choice_2;
                        cout << "Podmenu Kruskala:\n";
                        cout << "1. Kruskal - lista sasiedztwa\n";
                        cout << "2. Kruskal - macierz incydencji\n";
                        cout << "3. Powrot do menu glownego\n";
                        cout << "Wybierz opcje: ";
                        cin >> choice_2;

                        switch (choice_2) {
                            case 1:
                                if (!adjacencyList.empty()) {
                                    auto start = std::chrono::high_resolution_clock::now();
                                    auto result = Kruskal::execute(adjacencyList);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                            end - start).count();
                                    std::cout << "Czas wykonania: " << duration << " mikrosekund" << std::endl;

                                    int totalWeight = 0;
                                    cout << "Minimalne drzewo rozpinajace (Kruskal):\n";
                                    for (const auto &edge: result) {
                                        cout << "Krawedz " << edge.first.first << " - " << edge.first.second
                                             << ", waga: " << edge.second << endl;
                                        totalWeight += edge.second;
                                    }
                                    cout << "Suma wag: " << totalWeight << endl;
                                } else {
                                    cout << "Najpierw zainicjuj reprezentacje.\n";
                                }
                                break;
                            case 2:
                                if (!incidenceMatrix.empty()) {
                                    auto start = std::chrono::high_resolution_clock::now();
                                    auto result = KruskalIncidenceMatrix::execute(incidenceMatrix, weights);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                            end - start).count();
                                    std::cout << "Czas wykonania: " << duration << " mikrosekund" << std::endl;

                                    int totalWeight = 0;
                                    cout << "Minimalne drzewo rozpinajace (Kruskal - macierz incydencji):\n";
                                    for (const auto &edge: result) {
                                        cout << "Krawedz " << edge.first.first << " - " << edge.first.second
                                             << ", waga: " << edge.second << endl;
                                        totalWeight += edge.second;
                                    }
                                    cout << "Suma wag: " << totalWeight << endl;
                                } else {
                                    cout << "Najpierw zainicjuj reprezentacje.\n";
                                }
                                break;
                            case 3:
                                inSubmenu = false;
                                break;

                            default:
                                cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                        }
                    }
                    break;
                }
                case 6: {
                    bool inSubmenu = true;
                    while (inSubmenu) {
                        int choice_3;
                        cout << "Podmenu Dijkstry:\n";
                        cout << "1. Bellman-Ford - lista sasiedztwa\n";
                        cout << "2. Bellman-Ford - macierz incydencji\n";
                        cout << "3. Powrot do menu glownego\n";
                        cout << "Wybierz opcje: ";
                        cin >> choice_3;

                        switch (choice_3) {
                            case 1:
                                if (!adjacencyList.empty()) {
                                    int startVertex;
                                    cout << "Podaj wierzcholek poczatkowy: ";
                                    cin >> startVertex;

                                    auto start = std::chrono::high_resolution_clock::now();
                                    vector<int> distances = BellmanFord::shortestPath(startVertex, adjacencyList);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                            end - start).count();
                                    std::cout << "Czas wykonania: " << duration << " mikrosekund" << std::endl;


                                    cout << "Najkrotsze sciezki od wierzcholka " << startVertex << ":\n";
                                    for (int i = 0; i < distances.size(); ++i) {
                                        cout << "Do wierzcholka " << i << ": ";
                                        if (distances[i] == numeric_limits<int>::max()) {
                                            cout << "brak sciezki\n";
                                        } else {
                                            cout << distances[i] << endl;
                                        }
                                    }
                                } else {
                                    cout << "Najpierw zainicjuj reprezentacje.\n";
                                }
                                break;

                            case 2:
                                if (!incidenceMatrix.empty()) {
                                    int startVertex;
                                    cout << "Podaj wierzcholek poczatkowy: ";
                                    cin >> startVertex;

                                    auto start = std::chrono::high_resolution_clock::now();
                                    vector<int> distances = BellmanFordIncidenceMatrix::shortestPath(startVertex,incidenceMatrix,weights);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                                            end - start).count();
                                    std::cout << "Czas wykonania: " << duration << " mikrosekund" << std::endl;


                                    cout << "Najkrotsze sciezki od wierzcholka " << startVertex << ":\n";
                                    for (int i = 0; i < distances.size(); ++i) {
                                        cout << "Do wierzcholka " << i << ": ";
                                        if (distances[i] == numeric_limits<int>::max()) {
                                            cout << "brak sciezki\n";
                                        } else {
                                            cout << distances[i] << endl;
                                        }
                                    }
                                } else {
                                    cout << "Najpierw zainicjuj reprezentacje.\n";
                                }
                                break;

                            case 3:
                                inSubmenu = false;
                                break;

                            default:
                                cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                        }
                    }
                    break;
                }
                case 7:{
                    //symulacja, czyli generacja grafu, inicjalizacja reprezentacji oraz przeprowadzenie konkretnych algorytmow
                    bool inSubmenu = true;
                    while (inSubmenu) {
                        int choice_4;
                        cout << "Podmenu Symulacji:\n";
                        cout << "1. Dijkstra\n";
                        cout << "2. Bellman-Ford\n";
                        cout << "3. Kruskal\n";
                        cout << "4. Powrot do menu glownego\n";
                        cout << "Wybierz opcje: ";
                        cin >> choice_4;

                        switch (choice_4) {
                            case 1:
                                for (int i = 0; i < 50; ++i) {
                                    n = 220;
                                    density = 25;
                                    delete generator;
                                    generator = new GraphGenerator(n, density);
                                    generator->generateEdges();
                                    edges = generator->getEdges();
                                    weights = generator->getEdgeWeights();
                                    IncidenceMatrix matrix(n, density);
                                    matrix.setEdges(edges);
                                    matrix.setEdgeWeights(weights);
                                    matrix.createMatrix();
                                    incidenceMatrix = matrix.getMatrix();
                                    AdjacencyList adjList(n, density);
                                    adjList.setEdges(edges);
                                    adjList.setEdgeWeights(weights);
                                    adjList.createList();
                                    adjacencyList = adjList.getAdjList();
                                    int startVertex = 0;
                                    auto start = std::chrono::high_resolution_clock::now();
                                    vector<int> distances = Dijkstra::shortestPath(startVertex, adjacencyList);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                                    std::cout << "Czas wykonania Dijkstra List: " << duration << " mikrosekund" << std::endl;
                                    start = std::chrono::high_resolution_clock::now();
                                    distances = DijkstraIncidenceMatrix::shortestPath(startVertex,incidenceMatrix,weights);
                                    end = std::chrono::high_resolution_clock::now();
                                    duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start).count();
                                    std::cout << "Czas wykonania Dijkstra Matrix: " << duration << " mikrosekund" << std::endl;
                                }
                                break;
                            case 2:
                                for (int i = 0; i < 50; ++i) {
                                    n = 220;
                                    density = 50;
                                    delete generator;
                                    generator = new GraphGenerator(n, density);
                                    generator->generateEdges();
                                    edges = generator->getEdges();
                                    weights = generator->getEdgeWeights();
                                    IncidenceMatrix matrix(n, density);
                                    matrix.setEdges(edges);
                                    matrix.setEdgeWeights(weights);
                                    matrix.createMatrix();
                                    incidenceMatrix = matrix.getMatrix();
                                    AdjacencyList adjList(n, density);
                                    adjList.setEdges(edges);
                                    adjList.setEdgeWeights(weights);
                                    adjList.createList();
                                    adjacencyList = adjList.getAdjList();
                                    int startVertex = 0;
                                    auto start = std::chrono::high_resolution_clock::now();
                                    vector<int> distances = BellmanFord::shortestPath(startVertex, adjacencyList);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                                    std::cout << "Czas wykonania Bellman-Ford List: " << duration << " mikrosekund" << std::endl;
                                    start = std::chrono::high_resolution_clock::now();
                                    distances = BellmanFordIncidenceMatrix::shortestPath(startVertex,incidenceMatrix,weights);
                                    end = std::chrono::high_resolution_clock::now();
                                    duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start).count();
                                    std::cout << "Czas wykonania Bellman-Ford Matrix: " << duration << " mikrosekund" << std::endl;
                                }
                                break;
                            case 3:
                                for (int i = 0; i < 50; ++i) {
                                    n = 220;
                                    density = 99;
                                    delete generator;
                                    generator = new GraphGenerator(n, density);
                                    generator->generateEdges();
                                    edges = generator->getEdges();
                                    weights = generator->getEdgeWeights();
                                    IncidenceMatrix matrix(n, density);
                                    matrix.setEdges(edges);
                                    matrix.setEdgeWeights(weights);
                                    matrix.createMatrix();
                                    incidenceMatrix = matrix.getMatrix();
                                    AdjacencyList adjList(n, density);
                                    adjList.setEdges(edges);
                                    adjList.setEdgeWeights(weights);
                                    adjList.createList();
                                    adjacencyList = adjList.getAdjList();
                                    auto start = std::chrono::high_resolution_clock::now();
                                    auto result = Kruskal::execute(adjacencyList);
                                    auto end = std::chrono::high_resolution_clock::now();
                                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                                    std::cout << "Czas wykonania Kruskal List: " << duration << " mikrosekund" << std::endl;
                                    start = std::chrono::high_resolution_clock::now();
                                    result = KruskalIncidenceMatrix::execute(incidenceMatrix, weights);
                                    end = std::chrono::high_resolution_clock::now();
                                    duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start).count();
                                    std::cout << "Czas wykonania Kruskal Matrix: " << duration << " mikrosekund" << std::endl;
                                }
                                break;
                            case 4:
                                inSubmenu = false;
                                break;
                            default:
                                cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                        }
                    }
                    break;
                }
                case 8:
                    delete generator;
                    return;

                default:
                    cout << "Nieprawidlowa opcja. Sprobuj ponownie.\n";
                    break;
            }
        }
    }
};

int main() {
    Main::run();
    return 0;
}
