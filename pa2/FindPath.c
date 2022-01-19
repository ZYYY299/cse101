#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

void printDist(FILE* out, Graph G, int s, int u)
{
	 fprintf(out,"\n\n");
	 if(s>0 && s <=G->order && u>0 && u<=G->order)
	 {
		    if(getDist(G,u)==0)
		     {
                 if(s==u)
                 {
                	 fprintf(out,"The distance from %d to %d is %d",s,u,0);
                 }
		     }
		    else if(getDist(G,u)==-1)
		    {
		    	 fprintf(out,"The distance from %d to %d is infinity",s,u);
		    }
		    else
		     {
		    	 fprintf(out,"The distance from %d to %d is %d",s,u,getDist(G,u));
		     }
	 }

}
void printPath(FILE* out,List L,Graph G,int s, int u)
{
	fprintf(out,"\n");
	 if(getDist(G,u)==0)
			     {
	                 if(s==u)
	                 {
	                	 fprintf(out,"A shortest %d-%d path is: %d",s,u,s);
	                 }
	                 return;

			     }
			 else if(getDist(G,u)==-1)
			 {

				 fprintf(out,"No %d-%d  path exists",s,u);
				 return;
			 }



	fprintf(out,"A shortest %d-%d path is: ",s,u);
	   for(moveFront(L); index(L)>=0; moveNext(L)){
	      fprintf(out,"%d ", get(L));
	   }

}
int main(int argc, char* argv[]){
	 int n=0,a=0, b=0;
	 List L=newList();

	 Graph G = NULL;
	// Checking number of argument provided is write or wrong.
    if(argc!=3)
    {
    	fprintf( stderr, "The %d number of argument provided. We need two number of arguments.", argc-1);
        exit(1);
    }

    // Opening file for reading and writing

	FILE* readFile=fopen(argv[1],"r");
	FILE* writeFile=fopen(argv[2],"w");

	// Checked file processing

    if(readFile==NULL)
    {
    	fprintf(stderr,"The error in processing file.");
    	exit(1);
    }


 if(fscanf(readFile,"%d",&n)!=EOF)
 G = newGraph(n);
 int flag=0;
	 while(fscanf(readFile,"%d%d",&a,&b)!=EOF)
	 {
		 if(flag==-1 && a==0 && b==0)
		 {
			break;
		 }
		 if(a==0 && b==0)
		 {
			flag=-1;
			 printGraph(writeFile, G);
			continue;
		 }
		 if(flag==0)
		 {

			 addEdge(G,a,b);
		 }
		 else
		 {
			 BFS(G,a);
		     printDist(writeFile,G,a,b);
		     getPath(L,G,b);
		     printPath(writeFile,L,G,a,b);
		     freeList(&L);
		     L=newList();
		 }

	 }




    return (0);
}
