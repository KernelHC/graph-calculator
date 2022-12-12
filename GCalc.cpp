#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include "Exceptions.h"
#include "CalcMemory.h"
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#define SPACE ' '
#define SKIP_SPACES(str,it) while(*it==SPACE){++it;if(it==str.end())break;}

using std::set;
using std::map;
using std::vector;
using std::string;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cin;
using std::cout;
using std::cerr;




bool existsInOperatorTable (const char &c, const map<int,char> &operators);

bool isValidWho (const string &str);
bool isValidReset (const string &str);
bool isValidQuit (const string &str);
bool isValidDelete (const string &str);
bool isValidPrint (const string &str, const map<int,char> &operators);
bool isValidSave (const string &str, const map<int,char> &operators);
bool isValidLoad (const string &str);
bool isValidGraphName (const string &str);
bool isValidGraphLiteral (const string &str);
bool isValidFileName (const string &str);
bool isValidExpression (const string &str, const map<int,char> &operators);
bool isEmptyCommand (const string &str);
bool isValidSyntax (const string &str, const map<int,char> &operators);

int validateGraphs (const string &str, CalcMemory &calc , const map<int,char> &operators);
int getMaxPriority (const vector<string> &vec);
Graph loadFileIntoGraph (const string &file_name);
void saveGraphIntoFile (const Graph &g, const string &file_name);
Graph dissectedExpression (string str, CalcMemory &calc , const map<int,char> &operators);

void executeCommand (ostream &os, const string &str, CalcMemory &calc, const map<int,char> &operators);





bool existsInOperatorTable (const char &c, const map<int,char> &operators) {
    for (int i = 0; i < 6; i++) {
        if (operators.at(i) == c) return true;
    }
    return false;
}

bool isValidWho (const string &str) {
    if (str.find("who") == string::npos) return false;
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 'w') return false;
    ++it;
    if (*it != 'h') return false;
    ++it;
    if (*it != 'o') return false;
    ++it;
    if (it == str.end()) return true;
    SKIP_SPACES(str,it);
    if (it != str.end()) return false;
    return true;
}

bool isValidReset (const string &str) {
    if (str.find("reset") == string::npos) return false;
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 'r') return false;
    ++it;
    if (*it != 'e') return false;
    ++it;
    if (*it != 's') return false;
    ++it;
    if (*it != 'e') return false;
    ++it;
    if (*it != 't') return false;
    ++it;
    if (it == str.end()) return true;
    SKIP_SPACES(str,it);
    if (it != str.end()) return false;
    return true;
}

bool isValidQuit (const string &str) {
    if (str.find("quit") == string::npos) return false;
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 'q') return false;
    ++it;
    if (*it != 'u') return false;
    ++it;
    if (*it != 'i') return false;
    ++it;
    if (*it != 't') return false;
    ++it;
    if (it == str.end()) return true;
    SKIP_SPACES(str,it);
    if (it != str.end()) return false;
    return true;
}

bool isValidDelete (const string &str) {
    if (str.find("delete") == string::npos) return false;
    string tmp = "";
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 'd') return false;
    ++it;
    if (*it != 'e') return false;
    ++it;
    if (*it != 'l') return false;
    ++it;
    if (*it != 'e') return false;
    ++it;
    if (*it != 't') return false;
    ++it;
    if (*it != 'e') return false;
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    if (*it != '(') return false;
    ++it;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    while (*it != ')') {
        tmp += *it;
        ++it;
        if (it == str.end()) return false;
    }
    ++it;
    if (!isValidGraphName(tmp)) return false;
    if (it == str.end()) return true;
    SKIP_SPACES(str,it);
    if (it == str.end()) return true;
    return false;
}

bool isValidPrint (const string &str, const map<int,char> &operators) {
    if (str.find("print") == string::npos) return false;
    string tmp = "";
    int brackets_counter = 0;
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 'p') return false;
    ++it;
    if (*it != 'r') return false;
    ++it;
    if (*it != 'i') return false;
    ++it;
    if (*it != 'n') return false;
    ++it;
    if (*it != 't') return false;
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    if (*it != '(') return false;
    tmp += *it;
    ++brackets_counter;
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    while (*it != ')' && brackets_counter) {
        if (*it == ')') --brackets_counter;
        if (*it == '(') ++ brackets_counter;
        tmp += *it;
        ++it;
        if (it == str.end()) return false;
    }
    while (*it == ')') {
        tmp += *it;
        --brackets_counter;
        ++it;
        if (it == str.end()) return isValidExpression(tmp,operators);
    }
    SKIP_SPACES(str,it);
    if (it == str.end()) return true;
    return false;
}


bool isValidSave (const string &str, const map<int,char> &operators) {
    if (str.find("save") == string::npos) return false;
    string tmp = "";
    bool colon_is_allowed = false;
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 's') return false;
    ++it;
    if (*it != 'a') return false;
    ++it;
    if (*it != 'v') return false;
    ++it;
    if (*it != 'e') return false;
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    if (*it != '(') return false;
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    while (*it != ',' || colon_is_allowed) {
        tmp += *it;
        if (*it == '{') colon_is_allowed = true;
        if (*it == '}') colon_is_allowed = false;
        ++it;
        if (it == str.end()) return false;
    }
    if (!isValidExpression(tmp,operators)) return false;
    tmp = "";
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    while (*it != ')') {
        tmp += *it;
        ++it;
        if (it == str.end()) return false;
    }
    ++it;
    if (!isValidFileName(tmp)) return false;
    if (it == str.end()) return true;
    SKIP_SPACES(str,it);
    if (it == str.end()) return true;
    return false;
}


bool isValidLoad (const string &str) {
    if (str.find("load") == string::npos) return false;
    string tmp = "";
    string::const_iterator it = str.begin();
    SKIP_SPACES(str,it);
    if (*it != 'l') return false;
    ++it;
    if (*it != 'o') return false;
    ++it;
    if (*it != 'a') return false;
    ++it;
    if (*it != 'd') return false;
    ++it;
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    if (*it != '(') return false;
    ++it;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    while (*it != ')') {
        tmp += *it;
        ++it;
        if (it == str.end()) return false;
    }
    ++it;
    if (!isValidFileName(tmp)) return false;
    if (it == str.end()) return true;
    SKIP_SPACES(str,it);
    if (it == str.end()) return true;
    return false;
}


bool isValidGraphName (const string &str) {
    string::const_iterator it = str.begin();
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    if (!isalpha(*it)) return false;
    for (; it != str.end(); it++) {
        if (*it == SPACE) {
            ++it;
            if (it == str.end()) return true;
            SKIP_SPACES(str,it);
            if (it == str.end()) return true;
            else return false;
        }
        if (!isalnum(*it)) return false;
    }
    return true;
}

bool isValidGraphLiteral (const string &str) {
    return Graph::validGraphSyntax(str);
}

bool isValidFileName (const string &str) {
    string::const_iterator it = str.begin();
    if (it == str.end()) return false;
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    string tmp = "";
    while (it != str.end()) {
        if (*it == ',' || *it == '(' || *it == ')') return false;
        ++it;
    }
    return true;
}

bool isValidExpression (const string &str, const map<int,char> &operators) {
    string::const_iterator it = str.begin();
    if (it == str.end()) return false;
    int brackets_counter = 0;
    bool opening_bracket_allowed = true;
    bool closing_bracket_allowed = false;
    bool operator_allowed = false;
    bool graph_allowed = true;
    bool exclam_allowed = true;
    string current_graph = "";
    SKIP_SPACES(str,it);
    if (it == str.end()) return false;
    while (it != str.end()) {
        if (*it == '(' && opening_bracket_allowed) {
            ++brackets_counter;
            ++it;
            SKIP_SPACES(str,it);
            continue;
        }
        if (*it == ')' && closing_bracket_allowed && brackets_counter > 0) {
            --brackets_counter;
            ++it;
            SKIP_SPACES(str,it);
            continue;
        }
        if (existsInOperatorTable(*it,operators) && operator_allowed) {
            opening_bracket_allowed = true;
            closing_bracket_allowed = false;
            operator_allowed = false;
            graph_allowed = true;
            exclam_allowed = true;
            ++it;
            SKIP_SPACES(str,it);
            continue;
        }
        if (isalpha(*it) && graph_allowed) {
            if (*it == 'l') {
                current_graph += *it;
                ++it;
                if (it == str.end()) return isValidGraphName(current_graph);
                if (*it == 'o') {
                    current_graph += *it;
                    ++it;
                    if (it == str.end()) return isValidGraphName(current_graph);
                    if (*it == 'a') {
                        current_graph += *it;
                        ++it;
                        if (it == str.end()) return isValidGraphName(current_graph);
                        if (*it == 'd') {
                            current_graph += *it;
                            ++it;
                            if (it == str.end()) return isValidGraphName(current_graph);
                            SKIP_SPACES(str,it);
                            if (it == str.end()) return isValidGraphName(current_graph);
                            if (*it == '(') {
                                while (*it != ')') {
                                    current_graph += *it;
                                    ++it;
                                    if (it == str.end()) return false;
                                }
                                current_graph += *it;
                                ++it;
                                if (!isValidLoad(current_graph)) return false;
                                if (it == str.end()) return true;
                                current_graph = "";
                                opening_bracket_allowed = false;
                                closing_bracket_allowed = true;
                                operator_allowed = true;
                                graph_allowed = false;
                                exclam_allowed = false;
                                SKIP_SPACES(str,it);
                                continue;
                            }
                        }
                    }
                }
            }
            if (it == str.end()) return isValidGraphName(current_graph);
            while (isalnum(*it)) {
                current_graph += *it;
                ++it;
                if (it == str.end())
                    break;
            }
            if (!isValidGraphName(current_graph)) return false;
            current_graph = "";
            opening_bracket_allowed = false;
            closing_bracket_allowed = true;
            operator_allowed = true;
            graph_allowed = false;
            exclam_allowed = false;
            SKIP_SPACES(str,it);
            continue;
        }
        if (*it == '{' && graph_allowed) {
            while (*it != '}') {
                current_graph += *it;
                ++it;
                if (it == str.end())
                    return false;
            }
            current_graph += *it;
            ++it;
            if (!isValidGraphLiteral(current_graph)) return false;
            if (it == str.end()) return true;
            current_graph = "";
            opening_bracket_allowed = false;
            closing_bracket_allowed = true;
            operator_allowed = true;
            graph_allowed = false;
            exclam_allowed = false;
            SKIP_SPACES(str,it);
            continue;
        }
        if (*it == '!' && exclam_allowed) {
            ++it;
            SKIP_SPACES(str,it);
            continue;
        }
        return false;
    }
    if (brackets_counter) return false;
    return true;
}

bool isEmptyCommand (const string &str) {
    return (str.begin() == str.end());
}

bool isValidSyntax (const string &str, const map<int,char> &operators) {
    if (isValidWho(str) ||
        isValidReset(str) ||
        isValidQuit(str) ||
        isValidPrint(str,operators) ||
        isValidDelete(str) ||
        isValidSave(str,operators) ||
        isEmptyCommand(str)
        )
        return true;
    string::const_iterator it = str.begin();
    string current_str = "";
    SKIP_SPACES(str,it);
    if (it == str.end()) return true;
    if (!isalpha(*it)) throw SyntaxError();
    while (isalnum(*it)) {
        current_str += *it;
        ++it;
        if (it == str.end()) throw SyntaxError();
    }
    if (!isValidGraphName(current_str)) throw SyntaxError();
    current_str = "";
    SKIP_SPACES(str,it);
    if (it == str.end()) throw SyntaxError();
    if (*it != '=') throw SyntaxError();
    ++it;
    if (it == str.end()) throw SyntaxError();
    while (it != str.end()) {
        current_str += *it;
        ++it;
    }
    if (!isValidExpression(current_str,operators)) throw SyntaxError();
    return true;
}


int validateGraphs (const string &str, CalcMemory &calc , const map<int,char> &operators) {
    string::const_iterator it = str.begin();
    string current_graph = "";
    int count = 0;
    while (it != str.end()) {
        while (!isalpha(*it) && *it != '{'){
            ++it;
            if (it == str.end()) return count;
        }
        if (it == str.end()) return count;
        if (isalpha(*it)) {
            ++count;
            while (isalnum(*it)) {
                current_graph += *it;
                ++it;
                if (it == str.end()) break;
            }
            if (current_graph == "load" && it != str.end()) {
                SKIP_SPACES(str,it);
                if (it == str.end()) {
                    if (!(calc.containsGraph(current_graph))) throw GraphNotDefined(current_graph);
                    return count;
                }
                if (*it == '(') {
                    while (*it != ')') {
                        current_graph += *it;
                        ++it;
                    }
                    current_graph += *it;
                    if (it == str.end()) return count;
                    current_graph = "";
                    continue;
                }
            }
            if (!(calc.containsGraph(current_graph))) throw GraphNotDefined(current_graph);
            if (it == str.end()) return count;
            current_graph = "";
        }
        if (*it == '{') {
            ++count;
            while (*it != '}') {
                ++it;
            }
        }
    }
    return count;
}


int getMaxPriority (const vector<string> &vec) {
    int count = 0;
    int max_priority = 0;
    vector<string>::const_iterator it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (*it == "(") ++count;
        if (*it == ")") --count;
        if (count > max_priority) max_priority = count;
    }
    return max_priority;
}

Graph loadFileIntoGraph (const string &file_name) {
    const char* filename = file_name.c_str();
    ifstream infile(filename, std::ios_base::binary);
    if (!infile) throw FileError(file_name);
    Graph g;
    int vertices_num;
    int edges_num;
    int current_vertex_length;
    char *buffer;
    string current_vertex;
    infile.read((char*)&vertices_num, sizeof(int));
    infile.read((char*)&edges_num, sizeof(int));
    while (vertices_num) {
        infile.read((char*)&current_vertex_length, sizeof(int));
        buffer = new char[current_vertex_length+1];
        buffer[current_vertex_length] = '\0';
        infile.read(buffer, current_vertex_length);
        current_vertex = string(buffer);
        g.addVertex(current_vertex);
        --vertices_num;
        delete[] buffer;
    }
    while (edges_num) {
        infile.read((char*)&current_vertex_length, sizeof(int));
        buffer = new char[current_vertex_length+1];
        buffer[current_vertex_length] = '\0';
        infile.read(buffer, current_vertex_length);
        current_vertex = string(buffer);
        Vertex v1(current_vertex);
        delete[] buffer;
        infile.read((char*)&current_vertex_length, sizeof(int));
        buffer = new char[current_vertex_length+1];
        buffer[current_vertex_length] = '\0';
        infile.read(buffer, current_vertex_length);
        current_vertex = string(buffer);
        Vertex v2(current_vertex);
        g.addEdge(v1.getName(),v2.getName());
        --edges_num;
        delete[] buffer;
    }
    return g;
}

void saveGraphIntoFile (const Graph &g, const string &file_name) {
    int vertices_num = g.getVerticesNum();
    int edges_num = g.getEdgesNum();
    int buffer_index = 0;
    int begin_read = 0;
    int vertex_length = 0;
    string current_vertex = "";
    string current_edge1 = "";
    string current_edge2 = "";
    set<Vertex> vertices = g.getVertices();
    set<Edge> edges = g.getEdges();
    set<Vertex>::iterator v_it = vertices.begin();
    set<Edge>::iterator e_it = edges.begin();
    char* buffer = new char[g.getByteNum()];
    const char* filename = file_name.c_str();
    ofstream outfile(filename, std::ios_base::binary);
    if (!outfile) throw FileError(file_name);
    outfile.write((const char*)&vertices_num, sizeof(int));
    outfile.write((const char*)&edges_num, sizeof(int));
    while (v_it != vertices.end()) {
        current_vertex = (*v_it).getName();
        vertex_length = current_vertex.length();
        outfile.write((const char*)&vertex_length, sizeof(int));
        string::iterator it = current_vertex.begin();
        while (it != current_vertex.end()) {
            buffer[buffer_index] = *it;
            ++it;
            ++buffer_index;
        }
        outfile.write(buffer + begin_read, vertex_length);
        ++v_it;
        begin_read = buffer_index;
        current_vertex = "";
    }
    while (e_it != edges.end()) {
        current_edge1 = ((*e_it).getV1()).getName();
        current_edge2 = ((*e_it).getV2()).getName();
        vertex_length = current_edge1.length();
        outfile.write((const char*)&vertex_length, sizeof(int));
        string::iterator it1 = current_edge1.begin();
        while (it1 != current_edge1.end()) {
            buffer[buffer_index] = *it1;
            ++it1;
            ++buffer_index;
        }
        outfile.write(buffer + begin_read, vertex_length);
        begin_read = buffer_index;
        vertex_length = current_edge2.length();
        outfile.write((const char*)&vertex_length, sizeof(int));
        string::iterator it2 = current_edge2.begin();
        while (it2 != current_edge2.end()) {
            buffer[buffer_index] = *it2;
            ++it2;
            ++buffer_index;
        }
        outfile.write(buffer + begin_read, vertex_length);
        begin_read = buffer_index;
        current_edge1 = "";
        current_edge2 = "";
        ++e_it;
    }
    delete [] buffer;
}


Graph dissectedExpression (string str, CalcMemory &calc , const map<int,char> &operators) {
    int current_depth = 0;
    int graph_num = validateGraphs(str,calc,operators);
    int max_priority = 0;
    string current_str = "";
    string current_file = "";
    string::const_iterator it = str.begin();
    string::const_iterator tmp_it = str.begin();
    SKIP_SPACES(str,it);
    vector<string> morphed_string;
    vector<Graph> graph_vector;
    while (it != str.end()) {
        while (!isalpha(*it) && *it != '{'){
            if (*it == '!' || existsInOperatorTable(*it,operators)) {
                morphed_string.push_back("");
                *(--morphed_string.end()) = *it;
            }
            ++it;
            if (it == str.end()) break;
        }
        if (it == str.end()) break;
        if (isalpha(*it)) {
            while (isalnum(*it)) {
                current_str += *it;
                ++it;
                if (it == str.end()) break;
                if (current_str == "load") {
                    SKIP_SPACES(str,it);
                    if (it == str.end()) break;
                    if (*it == '(') {
                        while (tmp_it != it) ++tmp_it;
                        while (*tmp_it != ')') ++tmp_it;
                        --tmp_it;
                        while (*tmp_it == SPACE) --tmp_it;
                        ++tmp_it;
                        current_str = "";
                        ++it;
                        SKIP_SPACES(str,it);
                        while (it != tmp_it) {
                            current_file += *it;
                            ++it;
                        }
                        while (*it != ')') ++it;
                        ++it;
                        Graph loaded = loadFileIntoGraph(current_file);
                        graph_vector.push_back(loaded);
                        morphed_string.push_back(loaded.getGraphLiteral());
                    }
                    else break;
                }
            }
            if (current_str != "") {
                graph_vector.push_back(calc.getGraph(current_str));
                morphed_string.push_back((calc.getGraph(current_str)).getGraphLiteral());
                current_str = "";
            }
        }
        if (it == str.end()) break;
        if (*it == '{') {
            while (*it != '}') {
                current_str += *it;
                ++it;
            }
            current_str += *it;
            graph_vector.push_back(Graph(current_str));
            morphed_string.push_back(current_str);
            current_str = "";
        }
    }
    vector<string>::iterator extended_it = morphed_string.begin();
    vector<Graph>::iterator iterator = graph_vector.begin();
    bool is_first_graph = true;

    max_priority = getMaxPriority(morphed_string);
    while (morphed_string.size() > 1) {
        max_priority = getMaxPriority(morphed_string);
        while (current_depth < max_priority) {
            if (*extended_it == "(") {
                ++current_depth;
                if (current_depth == max_priority) break;
                ++extended_it;
                continue;
            }
            if (*extended_it == ")") {
                --current_depth;
                ++extended_it;
                continue;
            }
            if (isValidGraphLiteral(*extended_it)) {
                if (is_first_graph) {
                    ++extended_it;
                    is_first_graph = false;
                }
                else {
                    ++iterator;
                    ++extended_it;
                    continue;
                }
            }
            if (*extended_it == "!") {
                while (*(extended_it+1) == "!") ++extended_it;
                if (isValidGraphLiteral(*(extended_it+1))) {
                    *(iterator+1) = !(*(iterator+1));
                    extended_it = morphed_string.erase(extended_it);
                    continue;
                }
                else {
                    ++current_depth;
                    ++extended_it;
                    continue;
                }
            }
            ++extended_it;
        }
        if (*extended_it == "(") {
            ++extended_it;
            if (*extended_it == "!") {
                while (*(extended_it+1) == "!") ++extended_it;
                if (is_first_graph)
                    *(iterator) = !(*(iterator));
                else
                    *(iterator+1) = !(*(iterator+1));
                morphed_string.erase(extended_it);
                extended_it = morphed_string.begin();
                iterator = graph_vector.begin();
                is_first_graph = true;
                current_depth = 0;
            }
            if (isValidGraphLiteral(*extended_it)) {
                if (is_first_graph) {
                    is_first_graph = false;
                }
                else {
                    ++iterator;
                }
                if (*(extended_it+1) == ")") {
                    extended_it = morphed_string.erase(extended_it-1);
                    while (*extended_it != ")") ++extended_it;
                    morphed_string.erase(extended_it);
                    extended_it = morphed_string.begin();
                    iterator = graph_vector.begin();
                    is_first_graph = true;
                    current_depth = 0;
                    continue;
                }
                else {
                    ++extended_it;
                    ++extended_it;
                    if (*extended_it == "!") {
                        while (*(extended_it+1) == "!") ++extended_it;
                        *(iterator+1) = !(*(iterator+1));
                        morphed_string.erase(extended_it);
                        extended_it = morphed_string.begin();
                        iterator = graph_vector.begin();
                        is_first_graph = true;
                        current_depth = 0;
                        continue;
                    }
                    else {
                        --extended_it;
                        if (*extended_it == "+") *iterator = *iterator + *(iterator+1);
                        if (*extended_it == "-") *iterator = *iterator - *(iterator+1);
                        if (*extended_it == "*") *iterator = *iterator * *(iterator+1);
                        if (*extended_it == "^") *iterator = *iterator ^ *(iterator+1);
                        ++iterator;
                        graph_vector.erase(iterator);
                        --graph_num;
                        extended_it = morphed_string.erase(extended_it);
                        morphed_string.erase(extended_it);
                        extended_it = morphed_string.begin();
                        iterator = graph_vector.begin();
                        is_first_graph = true;
                        current_depth = 0;
                        continue;
                    }
                }
            }
        }
        else {
            if (*extended_it == "!") {
                while (*(extended_it+1) == "!") ++extended_it;
                if (is_first_graph)
                    *(iterator) = !(*(iterator));
                else
                    *(iterator+1) = !(*(iterator+1));
                morphed_string.erase(extended_it);
                extended_it = morphed_string.begin();
                iterator = graph_vector.begin();
                is_first_graph = true;
                current_depth = 0;
            }
            else {
                ++extended_it;
                ++extended_it;
                if (*extended_it == "!") {
                    while (*(extended_it+1) == "!") ++extended_it;
                    *(iterator+1) = !(*(iterator+1));
                    morphed_string.erase(extended_it);
                    extended_it = morphed_string.begin();
                    iterator = graph_vector.begin();
                    is_first_graph = true;
                    current_depth = 0;
                }
                else {
                    --extended_it;
                    if (*extended_it == "+") *iterator = *iterator + *(iterator+1);
                    if (*extended_it == "-") *iterator = *iterator - *(iterator+1);
                    if (*extended_it == "*") *iterator = *iterator * *(iterator+1);
                    if (*extended_it == "^") *iterator = *iterator ^ *(iterator+1);
                    ++iterator;
                    graph_vector.erase(iterator);
                    --graph_num;
                    extended_it = morphed_string.erase(extended_it);
                    morphed_string.erase(extended_it);
                    extended_it = morphed_string.begin();
                    iterator = graph_vector.begin();
                    is_first_graph = true;
                    current_depth = 0;
                }
            }
        }
    }
    return *(graph_vector.begin());
}


void executeCommand (ostream &os, const string &str, CalcMemory &calc, const map<int,char> &operators) {
    try{
        if (!isValidSyntax(str,operators)) throw SyntaxError();
        if (isEmptyCommand(str)) return;
        string::const_iterator it = str.begin();
        string current_str = "";
        set<string> tmp_set;

        if (isValidWho(str)) {
            os << calc;
            return;
        }

        if (isValidReset(str)) {
            calc.clearCalc();
            return;
        }

        if (isValidDelete(str)) {
            while (*it != '(') ++it;
            ++it;
            while (*it != ')') {
                current_str += *it;
                ++it;
            }
            if (!(calc.containsGraph(current_str))) throw GraphNotDefined(current_str);
            else calc.removeGraph(current_str);
            return;
        }

        if (isValidPrint(str,operators)) {
            string::const_iterator r_it = --str.end();
            while (*r_it != ')') --r_it;
            --r_it;
            while (*r_it == SPACE) --r_it;
            while (*it != '(') ++it;
            ++it;
            SKIP_SPACES(str,it);
            while (it != r_it) {
                current_str += *it;
                ++it;
            }
            current_str += *it;
            Graph g = dissectedExpression(current_str,calc,operators);
            os << g;
            return;
        }

        if (isValidSave(str,operators)) {
            string::const_iterator r_it = --str.end();
            string file_name = "";
            while (*r_it != ',') --r_it;
            while (*it != '(') ++it;
            ++it;
            while (it != r_it) {
                current_str += *it;
                ++it;
            }
            Graph to_save = dissectedExpression(current_str,calc,operators);
            SKIP_SPACES(str,it);
            ++it;
            SKIP_SPACES(str,it);
            while (*it != ')' && *it != SPACE) {
                file_name += *it;
                ++it;
            }
            saveGraphIntoFile(to_save,file_name);
            return;
        }

        it = str.begin();
        string graph_name = "";
        SKIP_SPACES(str,it);
        while (*it != '=' && *it != SPACE) {
            graph_name += *it;
            ++it;
        }
        SKIP_SPACES(str,it);
        ++it;
        SKIP_SPACES(str,it);
        while (it != str.end()) {
            current_str += *it;
            ++it;
        }
        Graph g = dissectedExpression (current_str,calc,operators);
        calc.addGraph (graph_name,g);

    }
    catch (const SyntaxError &e) {
        os << e.what() << endl;
        return;
    }
    catch (const InvalidVertexName &e) {
        os << e.what() << endl;
        return;
    }
    catch (const VertexNotExist &e) {
        os << e.what() << endl;
        return;
    }
    catch (const VertexDuplication &e) {
        os << e.what() << endl;
        return;
    }
    catch (const EdgeDuplication &e) {
        os << e.what() << endl;
        return;
    }
    catch (const GraphNotDefined &e) {
        os << e.what() << endl;
        return;
    }
    catch (const FileError &e) {
        os << e.what() << endl;
    }
}

int main (int argc, char *argv[]) {
    map<int,char> symbols = {{0,'+'}, {1,'-'}, {2,'*'}, {3,'='},
                             {4,'^'}, {5,'!'}, {6,'('}, {7,')'},
                             {8,'{'}, {9,'}'}, {10,'<'}, {11,'>'},
                             {12,'['}, {13,']'}, {14,','}, {15,';'}};

    map<int,char> operators = {{0,'+'}, {1,'-'}, {2,'*'},
                               {3,'^'}, {4,'('}, {5,')'}};

    CalcMemory calc;
    string input;
    if (argc == 1) {
        try {
            while (1) {
                cout << "Gcalc> ";
                if (!getline(cin, input) || isValidQuit(input)) return 0;
                executeCommand(cout, input, calc, operators);
            }
        }
        catch (const std::exception &e) {
            cerr << e.what() << endl;
            return 0;
        }
    }
    if (argc == 3) {
        try {
            char *input_file = argv[1];
            char *output_file = argv[2];
            ifstream from(input_file);
            ofstream to(output_file);
            if (!from) {
                cerr << "Error: cannot open file: " << input_file << endl;
                return 0;
            }
            if (!to) {
                cerr << "Error: cannot open file: " << input_file << endl;
                return 0;
            }
            while (getline(from, input)) {
                if (input.back() == 13 || (input.back() == '\n' && input.length() != 1))
                    input.erase(input.size() - 1);
                if (isValidQuit(input))
                    return 0;
                executeCommand(to, input, calc, operators);
            }
        }
        catch (const std::exception &e) {
            cerr << e.what() << endl;
            return 0;
        }
    }
    if (argc != 1 && argc != 3)
        cerr << "Error: invalid arguments"<< endl;

    return 0;
}