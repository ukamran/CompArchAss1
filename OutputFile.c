#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Chk_SRec.h"
#include "Output_File.h"


char name_of_file[100];
unsigned int length_of_name;

/*
void append_to_file(char[] filename) {

}

void output_file(int parsedRecord){
	fp = fopen("Output.dasm", "a"); //This means that we are going to write on this file
	//while (*parsedRecord) {
		// Dereference `line` and assign a new value '0'
		// then advance the pointer
	fprintf(fp, "%c", parsedRecord);
		//*(parsedRecord++) = '0';
	//}

	fclose(fp); //Don't forget to close the file when finished
}
*/

void create_file(char filename[], unsigned int filename_length) {
	// set the filename locally here
	int i;
	length_of_name = filename_length;
	for (i = 0; i < filename_length; i++) {
		name_of_file[i] = filename[i];
	}


	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
}

void append_file(char output[]) {
	FILE* fp;
	printf("This is the name of the file: %s \n", name_of_file);
	fp = fopen(name_of_file, "a");
	printf("Error here?");
	//fprintf(fp,"/n");
	fprintf(fp,"%s\n",output);
	fclose(fp);
}