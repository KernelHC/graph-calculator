#include <iostream>
#include <set>
#include <map>
#include <string>
#include "CalcMemory.h"
#include "Exceptions.h"
#include "Graph.h"

using std::set;
using std::map;
using std::string;
using std::endl;

void CalcMemory::addGraph (const string &name, const Graph &g) {
    graph_names.insert(name);
    if (!containsGraph(name)) {
        graphs_map.insert({name, g});
    }
    else {
        graphs_map[name] = g;
    }
}


void CalcMemory::removeGraph (const string &name) {
    graph_names.erase(graph_names.find(name));
    graphs_map.erase(graphs_map.find(name));
}


void CalcMemory::clearCalc () {
    graph_names.clear();
    graphs_map.clear();
}


bool CalcMemory::containsGraph (const string &str) const {
    set<string>::iterator it = graph_names.begin();
    while (it != graph_names.end()) {
        if (*it == str) return true;
        ++it;
    }
    return false;
}

Graph CalcMemory::getGraph (const string &str) const {
    if (!containsGraph(str)) throw GraphNotDefined(str);
    else return graphs_map.at(str);
}

std::ostream &operator << (std::ostream &os, const CalcMemory &calc) {
    set<string>::iterator it = calc.graph_names.begin();
    while (it != calc.graph_names.end()) {
        os << *it << endl;
        ++it;
    }
    return os;
}