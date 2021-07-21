/*
 - Print month.c
 - Print the specified month
 - In this example, the month array is a global
 - ECED 3403
 - 22 May 21
*/
#include "stdio.h"
#include "Array access.h"

void print_month(int mnum)
{
/*
 - Months[] is declared in Array access.c and accessed here
 - Since the compiler doesn't know where or what months[] is, we
   declare it in the header file (Array access.h)
 - Note sanity check on mnum before we access the array
*/
if (mnum <0 || mnum >= MONTHS)
	/* Invalid month number*/
	printf("Invalid month number: %d\n", mnum);
else
	/* Valid, print number and name */
	printf("Month num: %d Month name: %s\n", mnum, months[mnum]);

}