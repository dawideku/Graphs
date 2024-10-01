#include "AdjacencyList.h"
#include <iostream>
#include <iomanip>

using namespace std;

AdjacencyList::AdjacencyList(int n, int density) : GraphGenerator(n, density) {
    //inicjalizacja tablicy list sasiedztwa
    adjacencyList = new ListNode*[n];
    for (int i = 0; i < n; i++) {
        adjacencyList[i] = nullptr;
    }
}

AdjacencyList::~AdjacencyList() {
    //zwalnianie pamieci zajmowanej przez listy
    for (int i = 0; i < n; i++) {
        ListNode* current = adjacencyList[i];
        while (current != nullptr) {
            ListNode* next = current->next;
            delete current; //usuwanie aktualnego wezla i przejscie do kolejnego
            current = next;
        }
    }
    delete[] adjacencyList;
}

void AdjacencyList::createList() {
    adjList.resize(n); //zmiana rozmiaru wektora na liczbe wierzcholkow
    for (int i = 0; i < numEdges; i++) {
        int v1 = edgeList[i].v1;
        int v2 = edgeList[i].v2;
        int weight = edgeWeights[i];
        //tworzenie nowego wezla
        ListNode* node = new ListNode{v2, weight, adjacencyList[v1]};
        adjacencyList[v1] = node;

        adjList[v1].push_back({v2, weight}); //dodanie krawedzi do wektora
    }
}

void AdjacencyList::printList() const { //wyswietlenie listy
    for (int i = 0; i < n; i++) {
        cout << "A [" << i << "] =";
        ListNode* current = adjacencyList[i];
        while (current != nullptr) {
            cout << " (" << current->vertex << ", " << current->weight << ")";
            current = current->next;
        }
        cout << endl;
    }
}

const std::vector<std::vector<std::pair<int, int>>>& AdjacencyList::getAdjList() const {
    return adjList;
}

//ustawienie wierzcholkow i ich wag

void AdjacencyList::setEdges(const vector<Edge>& edges) {
    edgeList = edges;
    this->edges.clear();
    for (const auto& edge : edges) {
        this->edges.insert({min(edge.v1, edge.v2), max(edge.v1, edge.v2)});
    }
}

void AdjacencyList::setEdgeWeights(const vector<int>& weights) {
    edgeWeights = weights;
}
