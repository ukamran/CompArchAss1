/**
* DecodeAssembly. This file is used to decode instructions from their input hex values.
* Groups of instructions are used and the operands are subsequently parsed in their respective modules. 
* These groups are as follows:
    opset1: ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, BIT, BIC, BIS. 
	opsetg13: /movl, movlz, movls, movh
	 opsetg10: sra, rrc decoded here
	opsetg11: swpb, sxt
	opsetg12: swap
	opsetg23: mov
	opsetg3: cex
	opsetg4: setpri
	opsetg5: svc
	opsetg6: setcc, clrcc
	opsetg22: ld, st
	opsetg1: bra
	opsetg2: bl
	opsetg24: ldr, str

	Hexadecimal-binary-integer conversion is also performed within character arrays to facilitate decoding.
* ECED 3403
*  21 August 09
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"
#include "Instr.h"

#define DEBUG

//returns an integer equivalent of hexadecimal values
int hex_10(char input) {
	int output;
	switch (input) {
	case'A':
	case 'a':
		output = 10;
		break;
	case 'B':
	case 'b':
		output = 11;
		break;
	case 'C':
	case 'c':
		output = 12;
		break;
	case 'D':
	case 'd':
		output = 13;
		break;
	case 'E':
	case 'e':
		output = 14;
		break;
	case 'F':
	case 'f':
		output = 15;
		break;
	default:
		output = input - '0';
		break;
	}
	return output;
}

//creates a binary equivalent of hexadecimal values
void binary(char input_hex, char* output_binary) {
	
	const char *output_arr[] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	char op[4];
	int output_int;
	switch (input_hex) {
	case '0':
		output_int = 0;
		break;
	case '1':
		output_int = 1;
		break;
	case '2':
		output_int = 2;
		break;
	case '3':
		output_int = 3;
		break;
	case '4':
		output_int = 4;
		break;
	case '5':
		output_int = 5;
		break;
	case '6':
		output_int = 6;
		break;
	case '7':
		output_int = 7;
		break;
	case '8':
		output_int = 8;
		break;
	case '9':
		output_int = 9;
		break;
	case 'A':
	case 'a':
		output_int = 10;
		break;
	case 'B':
	case 'b':
		output_int = 11;
		break;
	case 'C':
	case 'c':
		output_int = 12;
		break;
	case 'D':
	case 'd':
		output_int = 13;
		break;
	case 'E':
	case 'e':
		output_int = 14;
		break;
	case 'F':
	case 'f':
		output_int = 15;
		break;
	default:
		printf("Invalid!");
		break;
	}

	//copies into the output array
	strcpy(op,output_arr[output_int]);
	for (int i = 0; i < 4; ++i) {
		output_binary[i] = op[i];
	}
}

//this function handles decodes output instructions if the first value is 2
int handle_two(int second_char, int third_char) {
	if (second_char < 4) {
		return 1; //BRA
	}
	else if ((second_char>=4 && second_char<8) ) {
			return 2; //CEX
	}	
	else if ((second_char == 8) && (third_char ==0)) {
		return 3; //SETPRI
	}
	else if (second_char == 8 && third_char == 1) {
		return 4; //SVC
	}
	else if (second_char == 8) {
		if (third_char >= 2 && third_char < 4) {
			return 5; //SETCC
		}
		else if (third_char == 4 || third_char==5) {
			return 6; //CLRCC
		}
	}
	else {
		printf("Invalid!");
	}

}

//this function decodes  instructions if the first hex character value is 4

int handle_four(int second_char, int third_char, int fourth_char) {
	switch (second_char) {
	case 0:
		return 7; //ADD
		break;
	case 1:
		return 8; //ADDC
		break;
	case 2:
		return 9; //SUB
		break; 
	case 3:
		return 10; //SUBC
		break;
	case 4:
		return 11; //DADD
		break;
	case 5:
		return 12; //CMP
		break;
	case 6:
		return 13; //XOR
		break;
	case 7:
		return 14; //AND
		break;
	case 8:
		return 15; //BIT
		break;
	case 9:
		return 16; //BIC
		break;
	case 10:
		return 17; //BIS
		break;
	case 12:
		if (third_char < 8) {
			return 18; //MOV
		}
		else if (third_char>=8 && third_char<12) {
			return 19; //SWAP
		}
		break;
	case 13:
		if (third_char == 0 || third_char == 4) {
			return 20; //SRA
		}
		else if (third_char == 8 || third_char == 12) {
			return 21; //RRC
		}
		else {
			printf("Invalid! \n");
		}
		break;
	case 14:
		if (third_char == 0 && fourth_char< 8) {
			return 22; //SWPB
		}
		else if (third_char==0 && fourth_char>=8) {
			return 23; //SXT
		}
		else {
			printf("Invalid! \n");
		}
		break;
	
	default:
		printf("Invalid! \n");
		break;
	}
	
}

/* this function decodes the input provided from the initial parsing that occurred in the display_and_check module.
 it then parses through each of the hex characters to, first, decode the instruction, and then pass the instruction with the input binary for further decoding into the 
 appropriate function (based on the grouping seen in the title).
*/
void decode_assembly(int low, int high, unsigned int address) {
	//retrieve the low value and the high byte value
	char lowhex[2];
	char highhex[2];
#ifdef DEBUG
	printf("At start of decode assembly\n");
#endif // DEBUG

	//store the hex value in char array
	sprintf(lowhex, "%02X", low);
	sprintf(highhex, "%02X", high);

	// retrieve the int equivalent of hex value. this is to ensure that we can use switch-case.
	int first_char = hex_10(lowhex[0]);
	int second_char = hex_10(lowhex[1]);
	int third_char = hex_10(highhex[0]);
	int fourth_char = hex_10(highhex[1]);
#ifdef DEBUG
	printf("Vars declared\n");
#endif // DEBUG

	char bin_first[4];
	char bin_second[4];
	char bin_third[4];
	char bin_fourth[4];

	binary(lowhex[0], bin_first);
#ifdef DEBUG
	printf("Low binary 1\n");

#endif // DEBUG


	binary(lowhex[1], bin_second);
#ifdef DEBUG
	printf("Low binary 2\n");

#endif // DEBUG


	binary(highhex[0], bin_third);

#ifdef DEBUG
	printf("Low binary 3\n");

#endif // DEBUG


	binary(highhex[1], bin_fourth);

#ifdef DEBUG
	printf("Low binary 4\n");
	printf("Binary conversion \n");

#endif // DEBUG



//store the input binary values. note that these are in reverse order from the instructions table seen in the manual.
	char bin_total[16] = {	bin_first[0], bin_first[1], bin_first[2],bin_first[3],
							bin_second[0],bin_second[1],bin_second[2],bin_second[3],
							bin_third[0],bin_third[1],bin_third[2],bin_third[3],
							bin_fourth[0], bin_fourth[1],bin_fourth[2],bin_fourth[3]
	};

	int instr_from_arr;

#ifdef DEBUG

	printf("First char: %d \n", first_char);
	printf("Second char: %d \n", second_char);
	printf("Third char: %d \n", third_char);
	printf("Fourth char: %d \n", fourth_char);

#endif // DEBUG


	//array of possible instructions. these will be mapped to return the appropriate value as required.
	const char *inst[] = { "BL","BRA","CEX","SETPRI","SVC","SETCC","CLRCC","ADD","ADDC","SUB","SUBC","DADD","CMP",
		"XOR","AND","BIT","BIC","BIS","MOV","SWAP","SRA","RRC","SWPB","SXT","LD","ST","MOVL",
		"MOVLZ","MOVLS","MOVH","LDR","STR",0 };
	
	// switch-case for the first character value
	switch (first_char) {
	case 12:
	case 13:
	case 14:
	case 15:
		instr_from_arr = 31;
		printf(inst[31]); //str
		break;
	case 0:
	case 1:
		instr_from_arr = 0;
		printf(inst[0]); //bl
		break;
	case 8:
	case 9:
	case 10:
	case 11:
		instr_from_arr = 30;
		printf(inst[30]); //ldr
		break;
	case 7:
		second_char >= 8 ? (instr_from_arr=29) : (instr_from_arr=28); //movh, movls
		printf(inst[instr_from_arr]);
		break;
	case 6:
		second_char >= 8 ? (instr_from_arr=27) : (instr_from_arr=26); //movlz, movl
		printf(inst[instr_from_arr]);
		break;
	case 5:
		if (second_char >= 12) {
			instr_from_arr = 25; //st
		}
		else if (second_char >= 8 && second_char < 12) {
			instr_from_arr = 24; //ld
		}
		else {
			printf("Invalid"); //can't be less than 8
		}
		printf(inst[instr_from_arr]);
		break;
	case 2:
		instr_from_arr = handle_two(second_char, third_char);
		printf(inst[handle_two(second_char, third_char)]);
		break;
	case 4:
		instr_from_arr = handle_four(second_char, third_char, fourth_char);
		printf(inst[handle_four(second_char, third_char, fourth_char)]);
		break;
	default:
		printf("Invalid!");
		break;
	};

	// these character arrays are defined to store the resulting instruction. this is an ugly but functional exercise.
	char opset1[4];
	char opsetg13[4];
	char opsetg10[4];
	char opsetg11[4];
	char opsetg12[4];
	char opsetg23[4];
	char opsetg3[4];
	char opsetg4[4];
	char opsetg5[4];
	char opsetg6[4];
	char opsetg22[4];
	char opsetg1[4];
	char opsetg2[4];
	char opsetg24[4];

	// the following if-else statements are used to copy the instructions into the appropriate character array 
	// and pass the instruction values into their respective functions to decode the operands.

	//ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, BIT, BIC, BIS decoding
	if (instr_from_arr == 7 || instr_from_arr == 8 || instr_from_arr == 9 || instr_from_arr == 10 || instr_from_arr == 11 || instr_from_arr == 12 || instr_from_arr == 13 || instr_from_arr == 14
		|| instr_from_arr == 15 || instr_from_arr == 16 || instr_from_arr == 17) {
		strcpy(opset1, inst[instr_from_arr]);
		decode_opset1(opset1, bin_total, address);
	}
	else if (instr_from_arr == 26 || instr_from_arr == 27 || instr_from_arr == 28 || instr_from_arr == 29) { //movl, movlz, movls, movh decoding
		strcpy(opsetg13, inst[instr_from_arr]);
		decode_opsetg13(opsetg13, bin_total, address);
		}
	//sra, rrc decoded here
	else if (instr_from_arr == 20 || instr_from_arr == 21) {
		strcpy(opsetg10, inst[instr_from_arr]);
		decode_opsetg10(opsetg10, bin_total, address);
	}
	else if (instr_from_arr == 22 || instr_from_arr == 23) { //swpb, sxt
		strcpy(opsetg11, inst[instr_from_arr]);
		decode_opsetg11(opsetg11, bin_total, address);
	}
	else if (instr_from_arr == 19) { //swap
		strcpy(opsetg12, inst[instr_from_arr]);
		decode_opsetg12(opsetg12, bin_total, address);
	}
	else if (instr_from_arr == 18) { //mov
		strcpy(opsetg23, inst[instr_from_arr]);
		decode_opsetg23(opsetg23, bin_total, address);
	}
	else if (instr_from_arr == 2) { //cex
		strcpy(opsetg3, inst[instr_from_arr]);
		decode_opsetg3(opsetg3, bin_total, address);
	}
	else if (instr_from_arr == 3) { //setpri
		strcpy(opsetg4, inst[instr_from_arr]);
		decode_opsetg4(opsetg4, bin_total, address);
	}
	else if (instr_from_arr == 4) { //svc
		strcpy(opsetg5, inst[instr_from_arr]);
		decode_opsetg5(opsetg5, bin_total, address);
	}
	else if (instr_from_arr == 5 || instr_from_arr == 6) { //setcc, clrcc
		strcpy(opsetg6, inst[instr_from_arr]);
		decode_opsetg6(opsetg6, bin_total, address);
	}
	else if (instr_from_arr == 24 || instr_from_arr == 25) { //ld, st
		strcpy(opsetg22, inst[instr_from_arr]);
		decode_opsetg22(opsetg22, bin_total, address);
	}
	else if (instr_from_arr ==  1) { //bra
		strcpy(opsetg1, inst[instr_from_arr]);
		decode_opsetg1(opsetg1, bin_total, address);
	}
	else if (instr_from_arr == 0) { //bl
		strcpy(opsetg2, inst[instr_from_arr]);
		decode_opsetg2(opsetg2, bin_total, address);
	}
	else if (instr_from_arr == 30 || instr_from_arr == 31) { //str, ldr
		strcpy(opsetg24, inst[instr_from_arr]);
		decode_opsetg24(opsetg24, bin_total, address);
	}
	else {
		printf("Not a valid instruction!");
	}

}