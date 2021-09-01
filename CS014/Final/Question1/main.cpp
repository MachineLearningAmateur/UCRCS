#include "AdjacencyMatrix.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    AdjacencyMatrix am("input.txt");

    //am.display();
  
    cout << "Performing BFS..." << endl;
    am.bfs(0);
    for (unsigned i = 0;i < am.vertices();++i) {
        cout << "Path: " << am.path(i) << " at a distance of " << am.distance(i) << endl;
    }
    cout << endl;

    cout << "Performing DFS..." << endl;
    am.dfs(0);
    for (unsigned i = 0;i < am.vertices();++i) {
        cout << "Path: " << am.path(i) << " at a distance of " << am.distance(i) << endl;
    }
    cout << endl;
    
    return 0;
}
