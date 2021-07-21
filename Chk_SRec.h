//#pragma once
/*
 - Module 1c: Header file
 - ECED 3403
 - 
*/
#define MAX_SREC_DATA	35				/* */
#define CHAR_MASK(x)	((x) & 0xFF)	/* int to char bit mask */

/* External entry points */
extern void display_and_check_srec(char*);
extern void decode_assembly(int, int);
