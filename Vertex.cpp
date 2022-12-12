#include <string>
#include "Exceptions.h"
#include "Vertex.h"

using std::string;

Vertex::Vertex(const string &str) {
    if (!validVertexName(str) || str == "")
        throw InvalidVertexName();
    name = str;
}

Vertex& Vertex::operator = (const Vertex &v) {
    if (this == &v) return *this;
    name = v.name;
    return *this;
}

bool Vertex::validVertexName (const string &str) {
    int bracket_counter = 0;
    string::const_iterator it = str.begin();
    while (it != str.end()) {
        if (*it != '[' && *it != ']' && *it != ';' && !isAlphanumeric(*it))
            return false;
        if (*it == ';' && bracket_counter <= 0)
            return false;
        if (*it == '[')
            ++bracket_counter;
        if (*it == ']')
            --bracket_counter;
        ++it;
    }
    if (bracket_counter != 0)
        return false;
    return true;
}

bool Vertex::operator == (const Vertex &v) const {
    return (v.name == name);
}

bool Vertex::operator != (const Vertex &v) const {
    return !(v.name == name);
}

bool Vertex::operator < (const Vertex &v) const {
    return (name < v.name);
}

string Vertex::getName() const {
    return name;
}


bool Vertex::isAlphanumeric (const char &c) {
    return ((c >= 'A' && c <= 'z') || (c >= '0' && c <= '9'));
}

std::ostream& operator << (std::ostream &os, const Vertex &v) {
    os << v.name;
    return os;
}