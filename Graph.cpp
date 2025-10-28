#include "../include/Graph.h"

Graph::Graph(int vertices) : numVertices(vertices) {
    adj.resize(vertices);
}

void Graph::addEdge(int v, int w) {
    // Add w to v’s list and v to w's list for an undirected graph
    if (v < numVertices && w < numVertices) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
}

void Graph::printGraph() const {
    std::cout << "\n--- Adjacency List ---" << std::endl;
    for (int v = 0; v < numVertices; ++v) {
        std::cout << "Vertex " << v << ":";
        for (auto x : adj[v])
            std::cout << " -> " << x;
        std::cout << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}
