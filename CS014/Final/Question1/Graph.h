#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>

class Graph {
    protected:
        std::vector<int> _distances;
        std::vector<int> _previous;
    public:
        Graph() { }
        virtual int vertices() const = 0;
        virtual int edges() const = 0;
        virtual int distance(int) const = 0;
        virtual void bfs(int) = 0;
        virtual void dfs(int) = 0;
        virtual void display() const = 0;
};
#endif // __GRAPH_H__
