
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// structure for node of list.
typedef struct NodeObj
{
	int data;
	struct NodeObj *prev;
	struct NodeObj *next;
}Node;

typedef Node *nodeObj;
// structure for list
typedef struct
{
int len;
int index;
Node *front;
Node *back;
Node *cursor;
}ListObj;

typedef ListObj *List;


// node constructor
Node* nodeConstructor(int value, Node* prevlink, Node* nextlink)
{
  Node* construct=NULL;
  construct=(Node*)malloc(sizeof(Node));
  construct->data=value;
  construct->prev=prevlink;
  construct->next=nextlink;
  return construct;
}
// node Destructor
void nodeDestructor(Node* node)
{
  if(node!=NULL)
  {
	  free(node);
  }

}

// list constructor
List newList(void)
{
List list=(List)malloc(sizeof(ListObj));
list->len=0;
list->index=-1;
list->front=NULL;
list->back=NULL;
list->cursor=NULL;
return list;
}


// get length of list.
int length(List L)
{
	return L->len;
}

// get index of list.
int index(List L)
{
return L->index;
}

// get data of front node of list.
int front(List L)
{
if(L->len>0)
{
	return L->front->data;
}
return -1;
}

// get data of back node of list.
int back(List L)
{
	if(L->len>0)
	{
		return L->back->data;
	}
return -1;
}

// get data of cursor node.
int get(List L)
{
	if(L->len>0 && L->index>=0)
	{
		return L->cursor->data;
	}
return -1;
}


// clear list
void clear(List L)
{
 L->len=0;
 L->index=-1;
 L->front=NULL;
 L->back=NULL;
 L->cursor=NULL;
}

// set data list x.
void set(List L, int x)
{
if(L->len>0 && L->index>=0)
{
L->cursor->data=x;
}
}

// set cursor node of list to front.
void moveFront(List L)
{
	if(L->front!=NULL )
	{
		L->cursor=L->front;
		L->index=0;
	}

}

// set cursor node of list to back
void moveBack(List L)
{
	if(L->back!=NULL )
	{
		L->cursor=L->back;
		L->index=L->len-1;
	}
}

// set cursor node to previous node of list.
void movePrev(List L)
{
	if(L->cursor!=L->front && L->cursor!=NULL)
	{
		L->cursor=L->cursor->prev;
		L->index=L->index-1;
	}
	else if(L->cursor==L->front)
	{
	  L->cursor=NULL;
	  L->index=-1;
	}
}

// set cursor node to next node of list.
void moveNext(List L)
{
	if(L->cursor!=L->back && L->cursor!=NULL )
	{
		L->cursor=L->cursor->next;
		L->index=L->index+1;
	}
	else if(L->cursor==L->back)
	{
	  L->cursor=NULL;
	  L->index=-1;
	}
}
// insert new data to front of list
void prepend(List L, int x)
{
  if(L->front!=NULL)
  {
	Node *temp=L->front;
	L->front=nodeConstructor(x,NULL,temp);
	temp->prev=L->front;
	L->len=L->len+1;
	  if(L->index!=-1)
	  {
		L->index=L->index+1;
	  }
  }
  else
  {
	  L->back=nodeConstructor(x,NULL,NULL);
	  L->front=L->back;
	  L->len=L->len+1;
	  if(L->index!=-1)
	  {
		L->index=L->index+1;
	  }
  }
}

// insert new data to back of list.

void append(List L, int x)
{
	  if(L->back!=NULL)
	  {
		Node *temp=L->back;
		L->back=nodeConstructor(x,temp,NULL);
		temp->next=L->back;
		L->len=L->len+1;
	  }
	  else
	  {
		  L->front=nodeConstructor(x,NULL,NULL);
		  L->back=L->front;
		  L->len=L->len+1;
	  }
}

// insert new before the cursor node.

void insertBefore(List L, int x)
{
   if(L->cursor==L->front)
   {
      prepend(L,x);
   }
   else if(L->cursor!=NULL)
   {
	   Node* p=nodeConstructor(x,L->cursor->prev,L->cursor);
	   L->cursor->prev->next=p;
	   L->cursor->prev=p;
	   L->len=L->len+1;
	   L->index=L->index+1;
   }
}

// insert new data after the cursor data.

void insertAfter(List L, int x)
{
	if(L->back==L->cursor)
	{
	 append(L,x);
	}
else if(L->cursor!=NULL)
	   {
		   Node* p=nodeConstructor(x,L->cursor,L->cursor->next);
		   L->cursor->next->prev=p;
		   L->cursor->next=p;
		   L->len=L->len+1;
	   }
}


// delete front node of list
void deleteFront(List L)
{

if(L->front!=NULL)
{
Node *temp=NULL;
if(L->front->next!=NULL)
{
        temp=L->front;
        L->front->next->prev=NULL;
	L->front=L->front->next;
	L->len=L->len-1;
	if(L->index!=-1)
	{
	L->index=L->index-1;
	}
	if(L->cursor==temp)
	{
	L->cursor=NULL;
	L->index=-1;
	}
}
else
{
       temp=L->front;
	L->front=NULL;
	L->back=NULL;
	L->len=L->len-1;
	L->index=-1;
	L->cursor=NULL;
}
 nodeDestructor(temp);
}
}

// delete back node of list

void deleteBack(List L)
{
	if(L->back!=NULL)
	{
	Node *temp=NULL;
	if(L->back->prev!=NULL)
	{
		temp=L->back;
	        L->back->prev->next=NULL;
		L->back=L->back->prev;
		L->len=L->len-1;
		if(temp==L->cursor)
		{
	            L->cursor=NULL;
	            L->index=-1;
		}
	}
	else
	{
		temp=L->back;
		L->front=NULL;
		L->back=NULL;
		L->len=L->len-1;
		L->index=-1;
		L->cursor=NULL;
	}
	nodeDestructor(temp);
	}
}

// delete cursor node of list.
void delete(List L)
{
if(L->cursor==L->front)
{
	deleteFront(L);
}
else if(L->cursor==L->back)
{
    deleteBack(L);
}

else
{


if(L->cursor!=NULL)
{
if(L->cursor->next!=NULL)
{
	L->cursor->next->prev=L->cursor->prev;
}
else if(L->cursor->prev!=NULL)
{
	L->cursor->prev->next=NULL;
}
if(L->cursor->prev!=NULL)
{
	L->cursor->prev->next=L->cursor->next;
}
else if(L->cursor->next!=NULL)
{
	L->cursor->next->prev=NULL;
}

L->index=-1;
L->len=L->len-1;
nodeDestructor(L->cursor);
}
}
}

//save list data with separated by space in output file.
void printList(FILE* out, List L)
{
	moveFront(L);
	int n=L->len;
 for(int i=0;i<n;i++)
 {
	 int x = get(L);
	 	 fprintf(out,"%d ",x);
	 	 moveNext(L);
 }
}

// compare two list and if both list status is same then return true.
bool equals(List A, List B)
{
  if(A->len==B->len)
  {
  if(A->front!=NULL && B-> front!=NULL)
  {
  moveFront(A);
  moveFront(B);
  while(index(A)>=0)
  {
  if(A->cursor->data!=B->cursor->data)
  {
  return false;
  }
  moveNext(A);
  moveNext(B);
  }
  }
  	  return true;
  }
  return false;
}

// copy list to new list and  cursor set undefined for new list.

List copyList(List L)
{
List list=(List)malloc(sizeof(ListObj));
list->len=L->len;
list->index=-1;
list->cursor=NULL;
list->front=L->front;
list->back=L->back;
return list;
}
// concatenation of list
List concatList(List A, List B)
{
  List C= newList();
  C=A;
  C->back->next=B->front;
  B->front->prev=A->back;
  return C;

}
// Destructor for list
void freeList(List* pL)
{
	   Node *temp=NULL;
	   int i=0;
	   for(moveFront(*pL); index(*pL)>=0; moveNext(*pL)){
		   if(i>0)
		   {
		   temp->next=NULL;
		   }
		    if((*pL)->front->next==NULL)
		   {
		   break;
		   }
		   temp=(*pL)->cursor;
	          nodeDestructor((*pL)->cursor->prev);
	          temp->prev=NULL;
	          i++;
	   }
	    (*pL)->front=NULL;
	    (*pL)->back=NULL;
	    nodeDestructor(temp);
	    free(*pL);
	   *pL=NULL;
}
