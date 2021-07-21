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
extern void decode_opsetg13(char input1[], char input2[16]);
extern void decode_opsetg10(char input1[], char input2[16]);
extern void decode_opsetg3(char input1[], char input2[16]);
extern void decode_opsetg4(char input1[], char input2[16]);
extern void decode_opsetg5(char input1[], char input2[16]);
extern void decode_opsetg6(char input1[], char input2[16]);
extern void decode_opsetg23(char input1[], char input2[16]);
extern void decode_opsetg11(char input1[], char input2[16]);
extern void decode_opsetg12(char input1[], char input2[16]);


