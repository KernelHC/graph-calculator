#ifndef CALCMEMORY_H_
#define CALCMEMORY_H_

#include <iostream>
#include <set>
#include <map>
#include <string>
#include "Graph.h"

using std::set;
using std::map;
using std::string;

class CalcMemory {
    set<string> graph_names;
    map<string,Graph> graphs_map;

public:
    CalcMemory() = default;
    ~ CalcMemory() = default;
    void addGraph (const string &name, const Graph &g);
    void removeGraph (const string &name);
    void clearCalc ();
    bool containsGraph (const string &str) const ;
    Graph getGraph (const string &str) const ;
    friend std::ostream &operator << (std::ostream &os, const CalcMemory &calc);
};

#endif