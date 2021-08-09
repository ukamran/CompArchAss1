/*
 - Array access.c
 - Examples of how we can create one-dimensional arrays in C
 - Accessing months of year
 - ECED 3403
 - 22 May 21
*/
#include <stdio.h>
#include "Array access.h"

/*
 - Defining (creating) an array of an unspecified length
 - Remember that months[] is an array of character pointers (char *)
 - Each element in the array (starting at 0) contains the address of the
   string.
 - For example months[2] has the address of the first character in the string
   Feb ('F'). Since this is a character array, the characters are stored 
   contiguously.  Each string is 4 characters long, the printable characters,
   such as 'F', 'e', and 'b', and the NUL character, '\0', indicating the end-of-string.
 - The designer must ensure we don't fall-off either end of the array.
*/
char* months[] = {
"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

main()
{
/*
 - Call print_month() to print the months
*/
int i;

for (i=0; i<MONTHS; i++)
	print_month(i);

getchar();

}
