#include <stdbool.h>
#ifndef LIST_H_
#define LIST_H_
typedef struct NodeObj
{
	int data;
	struct NodeObj *prev;
	struct NodeObj *next;
}Node;

typedef struct
{
int len;
int index;
Node *front;
Node *back;
Node *cursor;
}ListObj;

typedef ListObj *List;

Node* nodeConstructor(int, Node*, Node* );
void nodeDestructor(Node* );
List newList();
int length(List);
int index(List);
int front(List);
int back(List);
int get(List);
bool equals(List , List );
void clear(List );
void set(List , int );
void moveFront(List );
void moveBack(List );
void movePrev(List );
void moveNext(List );
void prepend(List , int );
void append(List , int );
void insertBefore(List , int );
void insertAfter(List , int );
void deleteFront(List);
void deleteBack(List);
void delete(List);
void printList(FILE* , List );
List copyList(List );
List concatList(List , List );
void freeList(List* );

#endif /* LIST_H_ */
