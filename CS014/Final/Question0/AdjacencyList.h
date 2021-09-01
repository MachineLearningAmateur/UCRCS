#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include "Graph.h"
#include <string>
#include <vector>
#include <climits>
#include <list>
#include <queue>
#include <stack>    

struct Vertex {
    std::list<std::pair<int, int>> neighbors;
    int i;
    int distance;
    std::string color;
    Vertex* prev;
    Vertex(int i) : i(i), distance(INT_MAX), color("WHITE"), prev(0) {}
    ~Vertex() {} 
};


class AdjacencyList : public Graph {
    private:
        std::vector<int> _distances;
        std::vector<int> _previous;
        std::vector<Vertex*> graph;
        int numVertices;
        int numEdges;
        void dfsVisit(Vertex* currVertex);
    public:
        AdjacencyList(std::string filename);
        int vertices() const;
        int edges() const;
        int distance(int source) const;
        std::string path(int i) const;
        void bfs(int);
        void dfs(int);
        void display() const;
        
};
#endif // __ADJACENCYLIST_H__

