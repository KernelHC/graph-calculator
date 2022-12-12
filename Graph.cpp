#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "Exceptions.h"

#define SPACE ' '
#define SKIP_SPACES(str,it) while(*it==SPACE){++it;if(it==str.end())break;}

using std::endl;
using std::cin;
using std::cout;
using std::set;
using std::string;


Graph::Graph(const string &str) {
    if (!validGraphSyntax(str)) throw SyntaxError();
    int brackets_counter = 0;
    string current_vertex = "";
    string current_edge = "";
    string::const_iterator it = str.begin();
    ++it;
    SKIP_SPACES(str,it);
    if (*it == '|' || *it == '}') return;
    while (it != --str.end() && *it != '|') {
        while (it != --str.end() && *it != ',' && *it != SPACE && *it != '|') {
            current_vertex += *it;
            ++it;
        }
        Vertex v(current_vertex);
        if (this->containsVertex (v)) throw VertexDuplication();
        this->vertices.insert (v);
        current_vertex = "";
        SKIP_SPACES(str,it);
        if (*it == ',') ++it;
        SKIP_SPACES(str,it);
        if (*it == '|') {
            ++it;
            SKIP_SPACES(str,it);
            break;
        }
    }
    while (it != --str.end()) {
        if (*it == '<') ++brackets_counter;
        while (it != --str.end() && (brackets_counter || *it != ',') && (brackets_counter || *it != SPACE)) {
            if (*it == '>') --brackets_counter;
            current_edge += *it;
            ++it;
        }
        Edge e(current_edge);
        if (this->containsEdge (e)) throw EdgeDuplication();
        if (!(this->containsVertex (e.getV1())) ||
            !(this->containsVertex (e.getV2()))) throw VertexNotExist(current_edge);
        this->edges.insert (e);
        current_edge = "";
        SKIP_SPACES(str,it);
        if (*it == ',') ++it;
        SKIP_SPACES(str,it);
    }
}



Graph &Graph::operator = (const Graph &g) {
    if (this == &g) return *this;
    vertices.clear();
    edges.clear();
    set<Vertex>::iterator v_it = (g.vertices).begin();
    set<Edge>::iterator e_it = (g.edges).begin();
    while (v_it != g.vertices.end()) {
        vertices.insert (*v_it);
        ++v_it;
    }
    while (e_it != g.edges.end()){
        edges.insert (*e_it);
        ++e_it;
    }
    return *this;
}


Graph Graph::operator + (const Graph &g) const {
    Graph g1 = g;
    set<Vertex>::iterator v_it = vertices.begin();
    set<Edge>::iterator e_it = edges.begin();
    while(v_it != vertices.end()) {
        g1.vertices.insert(*v_it);
        ++v_it;
    }
    while (e_it != edges.end()) {
        g1.edges.insert(*e_it);
        ++e_it;
    }
    return g1;
}


Graph Graph::operator ^ (const Graph &g) const {
    Graph g1 = *this + g;
    set<Vertex>::iterator v_it = g1.vertices.begin();
    set<Edge>::iterator e_it = g1.edges.begin();
    while(v_it != g1.vertices.end()) {
        if (!(this->containsVertex(*v_it)) || !(g.containsVertex(*v_it)))
            v_it = g1.vertices.erase(v_it);
        else
            ++v_it;
    }
    while (e_it != g1.edges.end()) {
        if (!(this->containsEdge(*e_it)) || !(g.containsEdge(*e_it)))
            e_it = g1.edges.erase(e_it);
        else
            ++e_it;
    }
    return g1;
}


Graph Graph::operator - (const Graph &g) const {
    Graph g1 = *this;
    set<Vertex>::iterator v_it = g1.vertices.begin();
    set<Edge>::iterator e_it = g1.edges.begin();
    while(v_it != g1.vertices.end()) {
        if ((g.containsVertex(*v_it)))
            v_it = g1.vertices.erase(v_it);
        else
            ++v_it;
    }
    while (e_it != g1.edges.end()) {
        if ((g.containsEdge(*e_it)))
            e_it = g1.edges.erase(e_it);
        else
            ++e_it;
    }
    e_it = g1.edges.begin();
    while (e_it != g1.edges.end()) {
        if (!(g1.containsVertex ((*e_it).getV1())) || !(g1.containsVertex ((*e_it).getV2())))
            e_it = g1.edges.erase(e_it);
        else
            ++e_it;
    }
    return g1;
}


Graph Graph::operator * (const Graph &g) const {
    Graph g1("{|}");
    set<Vertex>::iterator v_it1 = vertices.begin();
    set<Edge>::iterator e_it1 = edges.begin();
    set<Vertex>::iterator v_it2 = g.vertices.begin();
    set<Edge>::iterator e_it2 = g.edges.begin();
    for (; v_it1 != vertices.end(); v_it1++) {
        for (; v_it2 != g.vertices.end(); v_it2++) {
            Vertex v = combineVertices (*v_it1,*v_it2);
            g1.vertices.insert(v);
        }
        v_it2 = g.vertices.begin();
    }
    for (; e_it1 != edges.end(); e_it1++) {
        for (; e_it2 != g.edges.end(); e_it2++) {
            Vertex v1 = combineVertices ((*e_it1).getV1(),((*e_it2).getV1()));
            Vertex v2 = combineVertices ((*e_it1).getV2(),((*e_it2).getV2()));
            Edge e(v1,v2);
            g1.edges.insert(e);
        }
        e_it2 = g.edges.begin();
    }
    return g1;
}

Graph Graph::operator ! () const {
    Graph g = *this;
    g.edges.clear();
    set<Vertex>::iterator it1 = vertices.begin();
    set<Vertex>::iterator it2 = vertices.begin();
    for (; it1 != vertices.end(); it1++) {
        for (; it2 != vertices.end(); it2++) {
            if (*it1 == *it2) continue;
            Edge e(*it1,*it2);
            if (!(this->containsEdge(e)))
                g.edges.insert(e);
        }
        it2 = vertices.begin();
    }
    return g;
}

void Graph::addVertex (const string &str) {
    if (!(Vertex::validVertexName(str))) throw InvalidVertexName();
    Vertex v(str);
    if (this->containsVertex(v)) throw VertexDuplication();
    vertices.insert(v);
}

void Graph::addEdge (const string &v1, const string &v2) {
    if (v1 == v2) throw VertexDuplication();
    string e_str = "";
    e_str += string("<") + v1 + string(",") + v2 + string(">");
    Edge e(e_str);
    Vertex v_1(v1);
    Vertex v_2(v2);
    if (!(this->containsVertex(v1)) || !(this->containsVertex(v2))) throw VertexNotExist(e_str);
    if (!(Edge::validEdgeSyntax(e_str))) throw SyntaxError();
    if (this->containsEdge(e)) throw EdgeDuplication();
    edges.insert(e);
}

bool Graph::containsVertex (const Vertex &v) const {
    set<Vertex>::iterator it = vertices.begin();
    while (it != vertices.end()) {
        if (*it == v) return true;
        ++it;
    }
    return false;
}


bool Graph::containsEdge (const Edge &e) const {
    set<Edge>::iterator it = edges.begin();
    while (it != edges.end()) {
        if (*it == e) return true;
        ++it;
    }
    return false;
}



bool Graph::validGraphSyntax (const string &str) {
    if (str == "") return false;
    string current_vertex = "";
    string current_edge = "";
    int brackets_counter = 0;
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    if (*it != '{') return false;
    ++it;
    SKIP_SPACES(str,it);
    if (*it == '|') {
        ++it;
        SKIP_SPACES(str,it);
        if (*it == '}') return true;
        else return false;
    }
    if (it == str.end()) return false;
    if (*it == '}') return true;
    while (it != --str.end() && *it != '|') {
        while (it != --str.end() && *it != ',' && *it != SPACE && *it != '|') {
            current_vertex += *it;
            ++it;
        }
        if (!Vertex::validVertexName(current_vertex)) throw InvalidVertexName();
        current_vertex = "";
        SKIP_SPACES(str,it);
        if (*it == '}') return true;
        if (*it == '|') {
            ++it;
            SKIP_SPACES(str,it);
            if (it == str.end()) return false;
            if (*it == '}') return true;
            break;
        }
        SKIP_SPACES(str,it);
        if (*it == ',') ++it;
        SKIP_SPACES(str,it);
    }
    if (*it != '<') return false;
    while (it != --str.end()) {
        if (*it == '<') ++brackets_counter;
        while (it != --str.end() && (brackets_counter || *it != ',') && (brackets_counter || *it != SPACE)) {
            if (*it == '>') --brackets_counter;
            current_edge += *it;
            ++it;
        }
        if (!Edge::validEdgeSyntax(current_edge)) return false;
        current_edge = "";
        SKIP_SPACES(str,it);
        if (*it == ',') ++it;
        SKIP_SPACES(str,it);
        if (*it == '}') return true;
    }
    return false;
}


Vertex Graph::combineVertices (const Vertex &v1, const Vertex &v2) {
    string v_name = "";
    v_name += string("[") += v1.getName() += string(";") += v2.getName() += string("]");
    Vertex v(v_name);
    return v;
}

int Graph::getVerticesNum () const {
    int count = 0;
    set<Vertex>::iterator it = vertices.begin();
    while (it != vertices.end()) {
        ++count;
        ++it;
    }
    return count;
}

int Graph::getEdgesNum () const {
    int count = 0;
    set<Edge>::iterator it = edges.begin();
    while (it != edges.end()) {
        ++count;
        ++it;
    }
    return count;
}

set<Vertex> Graph::getVertices () const {
    return vertices;
}

set<Edge> Graph::getEdges () const {
    return edges;
}

int Graph::getByteNum () const {
    int byte_num = 0;
    set<Vertex>::iterator v_it = vertices.begin();
    set<Edge>::iterator e_it = edges.begin();
    while (v_it != vertices.end()) {
        byte_num += ((*v_it).getName()).length();
        ++v_it;
    }
    while (e_it != edges.end()) {
        byte_num += ((((*e_it).getV1()).getName())).length();
        byte_num += ((((*e_it).getV2()).getName())).length();
        ++e_it;
    }
    return byte_num;
}

string Graph::getGraphLiteral () const {
    string graph_literal = "{";
    set<Vertex>::iterator v_it = vertices.begin();
    set<Edge>::iterator e_it = edges.begin();
    while (v_it != vertices.end()) {
        graph_literal += (*v_it).getName();
        if (v_it != --vertices.end())
            graph_literal += ",";
        ++v_it;
    }
    graph_literal += "|";
    while (e_it != edges.end()) {
        graph_literal += "<";
        graph_literal += ((*e_it).getV1()).getName();
        graph_literal += ",";
        graph_literal += ((*e_it).getV2()).getName();
        graph_literal += ">";
        if (e_it != --edges.end())
            graph_literal += ",";
        ++e_it;
    }
    graph_literal += "}";
    return graph_literal;
}

std::ostream& operator << (std::ostream& os, const Graph &g) {
    set<Vertex>::iterator v_it = g.vertices.begin();
    set<Edge>::iterator e_it = g.edges.begin();
    while (v_it != g.vertices.end()) {
        os << *v_it << endl;
        ++v_it;
    }
    os << '$' << endl;
    while (e_it != g.edges.end()) {
        os << (*e_it).getV1() << SPACE;
        os << (*e_it).getV2() << endl;
        ++e_it;
    }
    return os;
}

