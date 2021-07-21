#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Output_File.h"
#include "Chk_SRec.h"


FILE* fp;

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