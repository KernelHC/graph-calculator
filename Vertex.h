#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <string>


using std::string;

class Vertex {
    string name;

    static bool isAlphanumeric(const char &c);
public:
    Vertex() = default;
    Vertex(const string &str);
    ~ Vertex() = default;
    Vertex(const Vertex &v): name(v.name) {}
    Vertex &operator = (const Vertex &v);
    bool operator == (const Vertex &v) const ;
    bool operator != (const Vertex &v) const ;
    bool operator < (const Vertex &v) const ;
    string getName() const ;
    static bool validVertexName (const string &str);

    friend std::ostream& operator << (std::ostream &os, const Vertex &v);
};

#endif