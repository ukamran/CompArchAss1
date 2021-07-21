#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define MAX_REC_LEN	256

FILE* infile;
char inrec[MAX_REC_LEN];

int main(int argc, char* argv[]) {
	/* File exists and is open, now read and display each record */
	while (fgets(inrec, MAX_REC_LEN, infile) > 0){
		printf("%s", inrec);
	}

	/* Close file */
	fclose(infile);

	/* Delay screen from disappearing */
	getchar();
	return 0;
}