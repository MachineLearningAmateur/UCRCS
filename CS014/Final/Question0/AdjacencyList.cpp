#include "AdjacencyList.h"
#include <fstream>
#include <iostream>

AdjacencyList::AdjacencyList(std::string filename) {
    std::fstream iFile;
    iFile.open(filename);
    iFile >> this->numVertices;
    numEdges = 0;
    for (unsigned int i = 0; i < numVertices; i++) {
        Vertex* vertex = new Vertex(i);
        this->graph.push_back(vertex);
    }

    int source, sink;
    while(iFile >> source) {
        // Read in an edge
        iFile >> sink;
        // Add edge to adjacency list (push-back)
        std::pair<int, int> edge(source, sink);
        this->graph.at(source)->neighbors.push_back(edge);
        numEdges++;
    }  
}

int AdjacencyList::vertices() const {
    return this->numVertices;
}

int AdjacencyList::edges() const {
    return numEdges; //rounds up
}

int AdjacencyList::distance(int i) const {
    return graph.at(i)->distance;
}

// The string path(int sink) function will print out the path from the source to the sink vertex passed in. 
// The format for this is {source->next->next->sink} with no whitespace. 
// For example, a path from source 0 to vertex 2 to sink 1 would be output as:
// {0->2->1}

std::string AdjacencyList::path(int sink) const {
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

//runtime complexity: O(m * n), n = number of vertices in vQ and m = number of pairs in neighbors
//space complexity: O(L), L = layers of vertex needed to be explored
void AdjacencyList::bfs(int source) {
    Vertex* start = this->graph.at(source); //O(1)
    start->color = "GRAY"; //O(1), discovered
    start->distance = 0; //O(1)
    start->prev = nullptr; //O(1)
    std::queue<Vertex*> vQ; //O(1)
    vQ.push(start);
    while (!vQ.empty()) { //O(n), n = number of vertexes in vQ
        Vertex* currVertex = vQ.front();
        vQ.pop();
        for (std::list<std::pair<int, int>>::iterator it = currVertex->neighbors.begin(); it != currVertex->neighbors.end(); it++) { //O(n), n = number of edges for currVertex
            Vertex* adjacent = graph.at((*it).second); //O(1), sets adjacent to adjacent vertex
            if (adjacent->color == "WHITE") { //O(1), undiscovered
                adjacent->color = "GRAY"; //O(1), discovered
                adjacent->distance = currVertex->distance + 1; //O(1)
                adjacent->prev = currVertex; //O(1)
                vQ.push(adjacent);
            }
        }
        currVertex->color = "BLACK"; //O(1), explored
    }
}

//runtime complexity: O(m * n), n = number of edges for currVertex, m = number of vertices
//space complexity: O(d), d = depth of each vertex
void AdjacencyList::dfs(int source) {
    for (unsigned int i = source; i <graph.size(); i++) { //O(m), m = number of vertices
        graph.at(i)->color = "WHITE"; //O(1)
        graph.at(i)->prev = nullptr; //O(1)
        graph.at(i)->distance = 0; //O(1)   
    }
    for (unsigned int i = source; i < graph.size(); i++) { //O(m)
        if (graph.at(i)->color == "WHITE"){ //O(1)
            dfsVisit(graph.at(i));
        }
    }
}

void AdjacencyList::dfsVisit(Vertex* currVertex) {
    currVertex->color = "GRAY"; //O(1)
    for (std::list<std::pair<int, int>>::iterator it = currVertex->neighbors.begin(); it != currVertex->neighbors.end(); it++) { //O(n), n = number of edges for currVertex
        Vertex* adjacent = graph.at((*it).second); //O(1)
        if (adjacent->color == "WHITE") { //O(1)
            adjacent->prev = currVertex; //O(1)
            adjacent->distance = currVertex->distance + 1; //O(1)
            dfsVisit(adjacent); 
        }
    }
    currVertex->color = "BLACK"; //O(1)
}

void AdjacencyList::display() const { //make graph?
    return;
}