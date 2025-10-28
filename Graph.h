#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>

// A simple generic Graph class using an adjacency list representation.
// It can be used for user connections, song locations, etc.
class Graph {
public:
    // Constructor to initialize the graph with a specific number of vertices
    Graph(int vertices);

    // Add an edge between two vertices (for an undirected graph)
    void addEdge(int v, int w);

    // Print the adjacency list representation of the graph
    void printGraph() const;

private:
    int numVertices;
    // Adjacency list: an array of lists
    std::vector<std::list<int>> adj;
};

#endif // GRAPH_H
