/*
 OutputFile.c: Creates a file output or appends to an existing file.
 ECED 3403
 21 August 09
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Chk_SRec.h"
#include "Output_File.h"


char name_of_file[100];
unsigned int length_of_name;

//this function creates a file with an input filename and a prescreibed length of the filename
void create_file(char filename[], unsigned int filename_length) {
	// set the filename locally here
	int i;
	length_of_name = filename_length;
	//store the name of the file in the global variable for use by the append_file function
	for (i = 0; i < filename_length; i++) {
		name_of_file[i] = filename[i];
	}

	//pointer to the file
	FILE* fp;
	//create the file with the set filename
	fp = fopen(filename, "w");
	//close the file
	fclose(fp);
}

void append_file(char output[]) {
	FILE* fp;
	//open the filename set in the global variable
	fp = fopen(name_of_file, "a");
	//append the char array output[] to the file  
	fprintf(fp,"%s\n",output);
	//close the file 
	fclose(fp);
}