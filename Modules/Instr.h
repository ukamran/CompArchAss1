//#pragma once
/*
 - This header file is used to declare the appropriate extern functions for each of the instructions
 - ECED 3403
 -
*/
#define MAX_SREC_DATA	35				/* */
#define CHAR_MASK(x)	((x) & 0xFF)	/* int to char bit mask */

/* External entry points */
extern void decode_opset1(char input1[], char input2[16]);
extern void decode_opsetg13(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg10(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg3(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg4(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg5(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg6(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg23(char input1[], char input2[16]);
extern void decode_opsetg11(char input1[], char input2[16]);
extern void decode_opsetg12(char input1[], char input2[16]);
extern void decode_opsetg1(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg24(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg2(char input1[], char input2[16],  unsigned int);
extern void decode_opsetg22(char input1[], char input2[16],  unsigned int);




