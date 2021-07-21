//#pragma once
/*
 - Module 1c: Header file
 - ECED 3403
 -
*/
#define MAX_SREC_DATA	35				/* */
#define CHAR_MASK(x)	((x) & 0xFF)	/* int to char bit mask */

/* External entry points */
extern void decode_opset1(char input1[], char input2[16]);
