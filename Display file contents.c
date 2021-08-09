/*
 This file has been used as is from the template provided by Dr Larry Hughes.
 Display the contents (records) of a file
 ECED 3403
 14 May 2021
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_REC_LEN	256

FILE *infile;
char inrec[MAX_REC_LEN];

int main(int argc, char* argv[])
{
/*
 - Open file in argv[1], read each record and display it
 - At EOF (end-of-file), stop reading and close file
 - If only one argument (.exe name), stop executing
*/

/* Check number of arguments */
if (argc == 1)
{
	printf("Missing file name\n");
	getchar();
	return -1;
}

/* argc >= 1, attempt to open file (0 = opened) */
if (fopen_s(&infile, argv[1], "r") != 0)
{
	printf("Error opening file >%s< - possibly missing\n", argv[1]);
	getchar();
	return -1;
}

/* File exists and is open, now read and display each record */
while (fgets(inrec, MAX_REC_LEN, infile) > 0)
{
	printf("%s", inrec);
}

/* Close file */
fclose(infile);

/* Delay screen from disappearing */
getchar();
return 0;

}

