#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Chk_SRec.h"
#include "Output_File.h"



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

void create_file(char filename[]) {
	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
}

void append_file(char filename[], char output[]) {
	FILE* fp;
	fp = fopen(filename, "a");
	//fprintf(fp,"/n");
	fprintf(fp,"%s\n",output);
	fclose(fp);
}