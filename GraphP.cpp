#include <iostream>
#include <string>
#include "Graph.h"
#include "GraphP.h"
#include "Exceptions.h"

using std::endl;
using std::cout;
using std::cerr;

Graph* create () {
    try {
        Graph *g = new Graph[sizeof(Graph)];
        return g;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const GraphNotDefined &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const FileError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

void destroy (Graph *graph) {
    try {
        if (!graph) throw NullArgument();
        delete [] graph;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return;
    }
}

Graph* addVertex (Graph *graph, const char *v) {
    try {
        if (!graph)
            throw NullArgument();
        std::string vertex(v);
        graph->addVertex(v);
        return graph;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

Graph* addEdge (Graph *graph, const char *v1, const char *v2) {
    try {
        if (!graph) throw NullArgument();
        std::string vertex1(v1);
        std::string vertex2(v2);
        graph->addEdge(v1,v2);
        return graph;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

void disp (const Graph *graph) {
    try {
        if (!graph) throw NullArgument();
        std::cout << *graph;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return;
    }
}

Graph* graphUnion (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out) {
    try {
        if (!graph_in1 || !graph_in2) throw NullArgument();
        *graph_out = *graph_in1 + *graph_in2;
        return graph_out;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

Graph* graphIntersection (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out) {
    try {
        if (!graph_in1 || !graph_in2) throw NullArgument();
        *graph_out = *graph_in1 ^ *graph_in2;
        return graph_out;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

Graph* graphDifference (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out) {
    try {
        if (!graph_in1 || !graph_in2) NullArgument();
        *graph_out = *graph_in1 - *graph_in2;
        return graph_out;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

Graph* graphProduct (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out) {
    try {
        if (!graph_in1 || !graph_in2) throw NullArgument();
        *graph_out = *graph_in1 * *graph_in2;
        return graph_out;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}

Graph* graphComplement (const Graph *graph_in, Graph *graph_out) {
    try {
        if (!graph_in) throw NullArgument();
        *graph_out = !(*graph_in);
        return graph_out;
    }
    catch (const SyntaxError &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const InvalidVertexName &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexNotExist &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const VertexDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const EdgeDuplication &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const NullArgument &e) {
        cout << e.what() << endl;
        return nullptr;
    }
    catch (const std::exception &e) {
        cerr << e.what() << endl;
        return nullptr;
    }
}