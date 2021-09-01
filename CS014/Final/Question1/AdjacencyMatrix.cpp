#include "AdjacencyMatrix.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std; 

AdjacencyMatrix::AdjacencyMatrix(std::string filename) {
    std::ifstream iFile;
    iFile.open(filename);
    numEdges = 0;
    iFile >> numVertices;
    matrix = new int*[numVertices];
    
    //initializes an empty matrix;
    for (int i = 0; i < numVertices; i++) {
        matrix[i] = new int[numVertices];
        Vertex* vertex = new Vertex();
        vertex->i = i;
        graph.push_back(vertex);
        for (int j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }

    //0 not present, 1 is present
    int source, sink;
    while (iFile >> source) {
        iFile >> sink;
        numEdges++;
        matrix[source][sink] = 1;
    }
}

int AdjacencyMatrix::vertices() const {
    return this->numVertices;
}

int AdjacencyMatrix::edges() const {
    return this->numEdges;
}

int AdjacencyMatrix::distance(int i) const {
    return graph.at(i)->distance;
}

std::string AdjacencyMatrix::path(int sink) const {
    std::string path;
    std::stack<Vertex*> sinkToSource; 
    Vertex *end = graph.at(sink);
    sinkToSource.push(end);
    while (end->prev != nullptr) {
        if (end->prev->i == sink) {
            break;
        }
        sinkToSource.push(end->prev);
        end = end->prev;
    }

    path = "{";
    while (!sinkToSource.empty()) {
        if (sinkToSource.size() == 1) {
            path += std::to_string(sinkToSource.top()->i);
            break;
        }
        path += std::to_string(sinkToSource.top()->i);
        path += "->";
        sinkToSource.pop();
    }
    path += "}";
    return path;
}

//runtime complexity: O(n^2), n = number of vertexes; worst case run time
//space complexity: O(L), L = layers of vertex needed to be explored
void AdjacencyMatrix::bfs(int source) {
    Vertex* start = this->graph.at(source); //O(1)
    start->color = "GRAY"; //O(1), discovered
    start->distance = 0; //O(1)
    start->prev = nullptr; //O(1)
    std::queue<Vertex*> vQ; //O(1)
    vQ.push(start); //O(1)
    while (!vQ.empty()) { //O(n), n = number of vertexes in vQ
        Vertex* currVertex = vQ.front();
        vQ.pop();
        for (unsigned int j = 0; j < numVertices; j++) { //O(n), n = number of vertexes
            if (matrix[currVertex->i][j] == 1) { //O(1)
                Vertex* adjacent = graph.at(j); //O(1)
                if (adjacent->color == "WHITE") {
                    adjacent->color = "GRAY"; //O(1)
                    adjacent->distance = currVertex->distance + 1; //O(1)
                    adjacent->prev = currVertex; //O(1)
                    vQ.push(adjacent); //O(1)
                }
            }
        }
        currVertex->color = "BLACK"; //O(1), explored
    }
}

//runtime complexity: O(n^2), n = number of vertexes
//space complexity: O(d), d = depth of each vertex
void AdjacencyMatrix::dfs(int source) {
    for (unsigned int i = source; i <graph.size(); i++) { //O(n), n = number of vertices
        graph.at(i)->color = "WHITE"; //O(1)
        graph.at(i)->prev = nullptr; //O(1)
        graph.at(i)->distance = 0; //O(1)   
    }

    for (unsigned int i = source; i < graph.size(); i++) { //O(n), n = number of vertices
        if (graph.at(i)->color == "WHITE"){ //O(1)
            dfsVisit(graph.at(i));
        }
    }
}

//runtime complexity: O
void AdjacencyMatrix::dfsVisit(Vertex* currVertex) {
    currVertex->color = "GRAY"; //O(1)
    for (unsigned int j = 0; j < numVertices; j++) { //O(n), number of vertexes
        if (matrix[currVertex->i][j] == 1) { //O(1)
            Vertex* adjacent = graph.at(j); //O(1)
            if (adjacent->color == "WHITE") { //O(1)
                adjacent->prev = currVertex; //O(1)
                adjacent->distance = currVertex->distance + 1; //O(1)
                dfsVisit(adjacent); //O(1)
            }
        }
    }
    currVertex->color = "BLACK"; //O(1)
}

void AdjacencyMatrix::display() const { //make graph?
    return;
}