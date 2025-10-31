#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>

// A simple generic Graph class using an adjacency list representation.
// It can be used for user connections, song locations, etc.
class Graph {
public:
    Graph(int vertices);
    void addEdge(int v, int w);
    void printGraph() const;
    
    std::list<int> getConnectionsOf(int v) const;


private:
    int numVertices;
    std::vector<std::list<int>> adj;
};

#endif
