#include<iostream>
#include<stdexcept>
#include <string.h>
#include"Dictionary.h"
#include<fstream>

#define MAX_WORD_LENGTH 256  // defined constant length of word
int main(int argc, char** argv)
{
	// Checking number of argument provided is write or wrong.
    if(argc!=3)
    {
    	fprintf( stderr, "The %d number of argument provided. We need two number of arguments.", argc-1);
        exit(1);
    }

    // Opening file for reading and writing

	FILE* readFile=fopen(argv[1],"r");
	std::ofstream  writeFile(argv[2]);

	// Checked file processing

    if(readFile==NULL)
    {
    	fprintf(stderr,"The error in processing file.");
    	exit(1);
    }
    Dictionary A;
    int count=0;
    	char *line=(char*)malloc(MAX_WORD_LENGTH*sizeof(char));

    	// Counting number of line in a input file

    	while(fgets(line, MAX_WORD_LENGTH ,readFile)!=NULL)
    	{
    		count++;
    		line[strcspn(line,"\n")]=0;
    		A.setValue(line,count);
    	}

    	writeFile<<A.to_string();
    	writeFile<<"\n";
        writeFile<<A.pre_string();
    	free(line);
}
