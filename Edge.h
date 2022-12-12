#ifndef EDGE_H_
#define EDGE_H_

#include <set>
#include <string>
#include "Vertex.h"


using std::string;
using std::set;

class Edge {
    Vertex v1;
    Vertex v2;

public:
    Edge(const string &str);
    Edge(const Vertex &ver_1, const Vertex &ver_2): v1(ver_1), v2(ver_2) {}
    ~ Edge() = default;
    Edge(const Edge &e): v1(e.v1), v2(e.v2) {}
    Edge &operator = (const Edge &e);
    const Vertex &getV1 () const ;
    const Vertex &getV2 () const ;
    bool operator == (const Edge &e) const ;
    bool operator < (const Edge &e) const ;
    bool verticesExist (const set<Vertex> &v_s);
    static bool validEdgeSyntax (const string &str);
};

#endif