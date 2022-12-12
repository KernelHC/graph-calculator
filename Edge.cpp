#include <iostream>
#include <set>
#include <string>
#include "Exceptions.h"
#include "Edge.h"
#include "Vertex.h"

#define SPACE ' '
#define COLON ','

using std::endl;
using std::cout;
using std::string;
using std::set;


Edge::Edge(const string &str): v1(), v2() {
    if (!validEdgeSyntax(str))
        throw SyntaxError();
    string v1_name = "";
    string v2_name = "";
    string::const_iterator it = str.begin();
    ++it;
    while (*it == SPACE) ++it;
    while (*it != COLON && *it != SPACE) {
        v1_name += *it;
        ++it;
    }
    ++it;
    while (*it == SPACE) ++it;
    if (*it == COLON) ++it;
    while (*it == SPACE) ++it;
    while (*it != '>' && *it != SPACE) {
        v2_name += *it;
        ++it;
    }
    v1 = v1_name;
    v2 = v2_name;
}

Edge& Edge::operator = (const Edge &e) {
    if (this == &e) return *this;
    v1 = e.v1;
    v2 = e.v2;
    return *this;
}

bool Edge::operator == (const Edge &e) const {
    return (e.v1 == v1 && e.v2 == v2);
}

bool Edge::operator < (const Edge &e) const {
    if (v1 == e.v1) return (v2 < e.v2);
    else return (v1 < e.v1);
}

const Vertex& Edge::getV1 () const {
    return v1;
}

const Vertex& Edge::getV2 () const {
    return v2;
}

bool Edge::verticesExist (const set<Vertex> &v_s) {
    bool v1_exists = false, v2_exists = false;
    set<Vertex>::const_iterator it = v_s.begin();
    while (it != v_s.end()) {
        if (*it == v1) v1_exists = true;
        if (*it == v2) v2_exists = true;
        ++it;
    }
    return (v1_exists && v2_exists);
}

bool Edge::validEdgeSyntax (const string &str) {
    string::const_iterator it = str.begin();
    bool colon_exists = false;
    while (it != str.end()) {
        if (*it == COLON) colon_exists = true;
        ++it;
    }
    return colon_exists;
}