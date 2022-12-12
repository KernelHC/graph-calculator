#ifndef GRAPH_P_H_
#define GRAPH_P_H_


#include "Graph.h"

Graph* create ();

void destroy (Graph *graph);

Graph* addVertex (Graph *graph, const char *v);

Graph* addEdge (Graph *graph, const char *v1, const char *v2);

void disp (const Graph *graph);

Graph* graphUnion (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out);

Graph* graphIntersection (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out);

Graph* graphDifference (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out);

Graph* graphProduct (const Graph *graph_in1, const Graph *graph_in2, Graph *graph_out);

Graph* graphComplement (const Graph *graph_in, Graph *graph_out);

#endif