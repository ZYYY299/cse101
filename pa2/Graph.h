#ifndef GRAPH_H_
#define GRAPH_H_
#include "List.h"
#define INF -1
#define NIL 0


typedef struct
{
int order;
int size;
int source;
List* neighbour;
int* color;
int* parent;
int* distance;
}GraphObj;
typedef GraphObj *Graph;
Graph newGraph(int);
int getOrder(Graph );
int getSize(Graph );
int getSource(Graph );
int getParent(Graph , int );
int getDist(Graph , int );
void getPath(List , Graph , int );
void makeNull(Graph );
void addEdge(Graph , int , int );
void addArc(Graph , int , int );
void BFS(Graph , int );
void printGraph(FILE* , Graph );
void freeGraph(Graph* );
#endif /* GRAPH_H_ */
