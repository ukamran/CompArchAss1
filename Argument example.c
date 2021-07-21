/*
 Module 1c: Argument example
 Display list of arguments
 ECED 3403
 14 May 2021 
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
/*
 - Read and display arguments from argument list
 - argc is count of number of arguments
 - argv[] is an array of character pointers, pointing to each argument
 - argv[0] is the name of the executable (.exe)
*/
int i;

i = 0;

/* Display each file from the argv[] list */
while (i < argc)
{
	printf("Argv[%d]: %s\n\n", i, argv[i]);
	i++;
}

/* Delay screen from disappearing */
getchar();

}

