#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__
#include <climits>
#include "Graph.h"
#include <string>
#include <vector>

using namespace std;

struct Vertex {
    int i;
    int distance;
    string color;
    Vertex* prev;
    Vertex() : distance(INT_MAX), color("WHITE"), prev(0) {}
    ~Vertex() {}
};

class AdjacencyMatrix : public Graph {
    private:
        int** matrix;
        std::vector<Vertex*> graph;
        int numEdges;
        int numVertices;
        std::vector<int> _distances;
        std::vector<int> _previous;
        void dfsVisit(Vertex* currVertex);
    public:
        AdjacencyMatrix(std::string filename);
        int vertices() const;
        int edges() const;
        int distance(int i) const;
        std::string path(int sink) const;
        void bfs(int source);
        void dfs(int source);
        void display() const;
};



#endif // __ADJACENCYMATRIX_H__
