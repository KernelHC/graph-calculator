#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <set>
#include <map>
#include <string>
#include "Vertex.h"
#include "Edge.h"

using std::set;
using std::string;

class Graph {
    set<Vertex> vertices;
    set<Edge> edges;

    static Vertex combineVertices (const Vertex &v1, const Vertex&v2);
public:
    Graph() = default;
    Graph(const string &str);
    ~Graph() = default;
    Graph(const Graph &g): vertices(g.vertices), edges(g.edges) {}
    Graph &operator = (const Graph &g);
    Graph operator + (const Graph &g) const ;
    Graph operator ^ (const Graph &g) const ;
    Graph operator - (const Graph &g) const ;
    Graph operator * (const Graph &g) const ;
    Graph operator ! () const ;
    void addVertex (const string &str);
    void addEdge (const string &v1, const string &v2);
    static bool validGraphSyntax (const string &str);
    bool containsVertex (const Vertex &v) const ;
    bool containsEdge (const Edge &e) const ;
    int getVerticesNum () const ;
    int getEdgesNum () const ;
    int getByteNum () const ;
    set<Vertex> getVertices () const ;
    set<Edge> getEdges () const ;
    string getGraphLiteral () const ;
    friend std::ostream& operator << (std::ostream& os, const Graph &g);
};

#endif