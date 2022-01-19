#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "List.h"
#define INF -1
#define NIL 0

typedef struct
{
int order;
int source;
int checkDG;
List* neighbour;
int* color;
int* parent;
int* distance;
}GraphObj;
typedef GraphObj *Graph;

typedef struct {
    List queue;
} QueueObj;
typedef QueueObj *Queue;

Queue createQueue()
{
     Queue queue = (Queue)malloc(
        sizeof(QueueObj));
    queue->queue=newList();
    return queue;
}
int isEmpty(Queue q)
{
	if( q->queue->len == 0)
	{
		return 0;
	}
    return q->queue->len;
}
void enqueue(Queue queue, int item)
{
    append(queue->queue, item);
}
int dequeue(Queue queue)
{
    if (isEmpty(queue)==0)
        return 0;
    int item = front(queue->queue);
    deleteFront(queue->queue);
    return item;
}

Graph newGraph(int n)
{
Graph graph=(Graph)malloc(sizeof(GraphObj));
graph->order=n;
graph->source=0;
graph->checkDG=0;
graph->neighbour=(List*)malloc((n+1)*sizeof(List));
graph->color=(int*)malloc((n+1)*sizeof(int));
graph->distance=(int*)malloc((n+1)*sizeof(int));
graph->parent=(int*)malloc((n+1)*sizeof(int));
for(int i=1;i<=n;i++)
{
graph->neighbour[i]=newList();
}
return graph;
}
int getOrder(Graph G)
{
return G->order;
}
int getSize(Graph G)
{
int size=0;
for(int i=1;i<=G->order;i++)
{
size=size+G->neighbour[i]->len;
}
if(G->checkDG==1)
{
return size;
}
int result=size/2;
return result;
}
int getSource(Graph G)
{
return G->source;
}
int getParent(Graph G, int u)
{
	if(G->source==0)
		{
		return 0;
		}
return G->parent[u];
}
int getDist(Graph G, int u)
{
	if(G->source==0 || u<1 || u>G->order )
	{
	return -1;
	}
return G->distance[u];
}
void getPath(List L, Graph G, int u)
{
	if(G->source==u)
	{
		append(L,G->source);
		return;
	}
	if(u<1 || u>G->order || G->source==0 || G->distance[u]==0)
	{
		append(L,0);
		return;
	}
   if(G->source==u)
   {
	   append(L,G->source);
	   return;
   }
   getPath(L,G,G->parent[u]);
   if(front(L)!=0)
   {
	   append(L,u);
   }

}
void makeNull(Graph G)
{
for(int i=0;i<=G->order;i++)
{
freeList(&(G->neighbour[i]));
G->neighbour[i]=newList();
}
}
void addEdge(Graph G, int u, int v)
{
	if(u>G->order || v>G->order ||u<1 ||v<1)
	{
           return;
	}

	int flag=0;

	for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u]))
	{
		       if(get(G->neighbour[u])==v)
		       {
		    	   flag=-1;
		    	   break;
		       }
     }
		if(flag==0)
	{

			if(front(G->neighbour[u])==-1)
			{
				append(G->neighbour[u],v);
			}
			else
			{
				if(front(G->neighbour[u])>v)
				{
				prepend(G->neighbour[u],v);
				}
				else if(back(G->neighbour[u])<v)
				{

					append(G->neighbour[u],v);
				}
				else
				{
					for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u]))
					{

						if(get(G->neighbour[u])>v)
					{
					insertBefore(G->neighbour[u],v);
					break;
					}
					}
				}


			}
////
if(front(G->neighbour[v])==-1)
	{
		append(G->neighbour[v],u);
	}
	else
	{
		if(front(G->neighbour[v])>u)
		{
			
		prepend(G->neighbour[v],u);
		}
		else if(back(G->neighbour[v])<u)
		{
			append(G->neighbour[v],u);
		}
		else
		{

		for(moveFront(G->neighbour[v]); index(G->neighbour[v])>=0; moveNext(G->neighbour[v]))
		{
			if(get(G->neighbour[v])>u)
		{
		insertBefore(G->neighbour[v],u);
		break;
		}
		}
		}


	}


	}

}

void addArc(Graph G, int u, int v)
{
	if(u>G->order || v>G->order ||u<1 ||v<1)
	{
           return;
	}
	G->checkDG=1;
	int flag=0;
	for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u])){
		       if(get(G->neighbour[u])==v)
		       {
		    	   flag=-1;
		    	   break;
		       }
		   }

	if(flag==0)
{
	if(front(G->neighbour[u])==-1)
			{
				append(G->neighbour[u],v);
			}
			else
			{
				if(front(G->neighbour[u])>v)
				{
				prepend(G->neighbour[u],v);
				}
				else if(back(G->neighbour[u])<v)
				{

					append(G->neighbour[u],v);
				}
				else
				{
					for(moveFront(G->neighbour[u]); index(G->neighbour[u])>=0; moveNext(G->neighbour[u]))
					{

						if(get(G->neighbour[u])>v)
					{
					insertBefore(G->neighbour[u],v);
					break;
					}
					}
				}


			}

}
}
void BFS(Graph G, int s)
{
	if(s>G->order || s<1)
	{
           return;
	}
	G->source=s;
	for(int i=1;i<=G->order;i++){
		        G->color[i] = 0; // white
		        G->distance[i] = -1;
		        G->parent[i] = 0;
			   }

	 G->color[s] = 1; // gray
	 G->distance[s] = 0;
     G->parent[s] = 0;
Queue q=createQueue();
enqueue(q,s);
while(isEmpty(q)!=0)
{
int x= dequeue(q);
if(x==0)
{
	continue;
}

for(moveFront(G->neighbour[x]); index(G->neighbour[x])>=0; moveNext(G->neighbour[x])){
	int y=get(G->neighbour[x]);
	if(G->color[y]==0)
	{

		 	 G->color[y] = 1; // gray
			 G->distance[y] = G->distance[x]+1;
		     G->parent[y] = x;
		     enqueue(q,y);
	}
	   }
G->color[x]=2; //black

}

}
void printGraph(FILE* out, Graph G)
{
for(int i=1;i<=G->order;i++)
{
	fprintf(out,"%d: ",i);
	for(moveFront(G->neighbour[i]); index(G->neighbour[i])>=0; moveNext(G->neighbour[i])){
            fprintf(out,"%d ",get(G->neighbour[i]));

		   }
	fprintf(out,"\n");
}
}
void freeGraph(Graph* pG)
{
	if((*pG)!=NULL)
	{
		for(int i=1;i<=(*pG)->order;i++)
		{
	       freeList(&((*pG)->neighbour[i]));
		}
		free((*pG)->neighbour);
		free((*pG)->color);
		free((*pG)->distance);
		free((*pG)->parent);
		free((*pG));
	}

	(*pG)=NULL;
}
