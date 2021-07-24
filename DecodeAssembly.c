#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"
#include "Instr.h"


int hex_10(char input) {
	int output;
	switch (input) {
	case'A':
		output = 10;
		break;
	case 'B':
		output = 11;
		break;
	case 'C':
		output = 12;
		break;
	case 'D':
		output = 13;
		break;
	case 'E':
		output = 14;
		break;
	case 'F':
		output = 15;
		break;
	default:
		output = input - '0';
		break;
	}
	return output;
}
void binary(char input_hex, char* output_binary) {
	
	const char *output_arr[] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1111" };
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
		output_int = 10;
		break;
	case 'B':
		output_int = 11;
		break;
	case 'C':
		output_int = 12;
		break;
	case 'D':
		output_int = 13;
		break;
	case 'E':
		output_int = 14;
		break;
	case 'F':
		output_int = 15;
		break;
	default:
		printf("Invalid!");
		break;
	}

	strcpy(op,output_arr[output_int]);
	for (int i = 0; i < 4; ++i) {
		output_binary[i] = op[i];
	}
}

/**
* 
char binary[4](char input) {
	char[4] output;
	switch (input_hex) {
	case'0':
		output = "0000";
		break;
	case '1':
		output = "0001";
		break;
	case '2':
		output = "0010";
		break;
	case '3':
		output = "0011";
		break;
	case '4':
		output = "0100";
		break;
	case '5':
		output = "0101";
		break;
	case '6':
		output = "0110";
		break;
	case '7':
		output = "0111";
		break;
	case '8':
		output = "1000";
		break;
	case '9':
		output = "1001";
		break;
	case 'A':
		output = "1010";
		break;
	case 'B':
		output = "1011";
		break;
	case 'C':
		output = "1100";
		break;
	case 'D':
		output = "1101";
		break;
	case 'E':
		output = "1110";
		break;
	case 'F':
		output = "1111";
		break;
	default:
		printf("Invalid!");
		break;
	}
	return output;
}
**/

int handle_two(int second_char, int third_char) {
	if (second_char < 4) {
		return 1; //BRA
	}
	else if ((second_char > 4) ) {
		if (third_char < 8) {
			return 2; //CEX
		}
	}	
	else if ((second_char == 8) && (third_char ==0)) {
		return 3; //SETPRI
	}
	else if (second_char == 8 && third_char == 1) {
		return 4; //SVC
	}
	else if (second_char == 8) {
		if (third_char >= 2 || third_char < 4) {
			return 5; //SETCC
		}
		else if (third_char >= 4) {
			return 6; //CLRCC
		}
	}

}

int handle_four(int second_char, int third_char) {
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
		else {
			return 19; //SWAP
		}
		break;
	case 13:
		if (third_char < 8) {
			return 20; //SRA
		}
		else {
			return 21; //RRC
		}
		break;
	case 14:
		if (third_char < 8) {
			return 22; //SWPB
		}
		else {
			return 23; //SXT
		}
		break;
	}
}

void decode_assembly(int low, int high, unsigned int address, char filename[]) {
	/*int lower_var = low;
	int higher_var = high;
	char first_char = lower_var.toString()[0];
	char second_char = lower_var.toString()[1];
	char third_char = higher_var.toString()[0];
	*/
	//int first_char = low[0];
	//int second_char = low[1];
	//int third_char = high[0];
	
	//TODO: Type checking to ensure only 2 digits passed!
	char lowhex[2];
	char highhex[2];

	sprintf(lowhex, "%02X", low);
	sprintf(highhex, "%02X", high);

	int first_char = hex_10(lowhex[0]);
	int second_char = hex_10(lowhex[1]);
	int third_char = hex_10(highhex[0]);

	char bin_first[4];
	char bin_second[4];
	char bin_third[4];
	char bin_fourth[4];

	binary(lowhex[0], bin_first);
	binary(lowhex[1], bin_second);
	binary(highhex[0], bin_third);
	binary(highhex[1], bin_fourth);

	char bin_total[16] = {	bin_first[0], bin_first[1], bin_first[2],bin_first[3],
							bin_second[0],bin_second[1],bin_second[2],bin_second[3],
							bin_third[0],bin_third[1],bin_third[2],bin_third[3],
							bin_fourth[0], bin_fourth[1],bin_fourth[2],bin_fourth[3]
	};

	int instr_from_arr;
	//char decoded_instr[];
	//printf("func low: %02x", low);
	//printf("func high: %02x", high);
	//int first_char = high / pow(10, 1);
	//int second_char = high % 10;
	//int third_char = low / pow(10, 1);

	//printf("First char: %d", first_char);
	//printf("Second char: %d", second_char);
	//printf("Third char: %d", third_char);


	const char *inst[] = { "BL","BRA","CEX","SETPRI","SVC","SETCC","CLRCC","ADD","ADDC","SUB","SUBC","DADD","CMP",
		"XOR","AND","BIT","BIC","BIS","MOV","SWAP","SRA","RRC","SWPB","SXT","LD","ST","MOVL",
		"MOVLZ","MOVLS","MOVH","LDR","STR",0 };
	
	//printf("Sanity check!");
	//int first_char = 9;
	//int second_char = 2;
	//int third_char = 3;
	switch (first_char) {
	case 9:
		instr_from_arr = 31;
		printf(inst[31]); //str
		break;
	case 0:
		instr_from_arr = 0;
		printf(inst[0]); //bl
		break;
	case 8:
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
		second_char > 8 ? (instr_from_arr = 25) : (instr_from_arr = 24); //st, ld
		printf(inst[instr_from_arr]);

		break;
	case 2:
		instr_from_arr = handle_two(second_char, third_char);
		printf(inst[handle_two(second_char, third_char)]);
		break;
	case 4:
		instr_from_arr = handle_four(second_char, third_char);
		printf(inst[handle_four(second_char, third_char)]);
		break;
	};

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


	if (instr_from_arr == 7 || instr_from_arr == 8 || instr_from_arr == 9 || instr_from_arr == 10 || instr_from_arr == 11 || instr_from_arr == 12 || instr_from_arr == 13 || instr_from_arr == 14
		|| instr_from_arr == 15 || instr_from_arr == 16 || instr_from_arr == 17) {
		strcpy(opset1, inst[instr_from_arr]);
		decode_opset1(opset1, bin_total);
	}
	else if (instr_from_arr == 26 || instr_from_arr == 27 || instr_from_arr == 28 || instr_from_arr == 29) { //movl, movlz, movls, movh decoding
		strcpy(opsetg13, inst[instr_from_arr]);
		decode_opsetg13(opsetg13, bin_total);
		}
	else if (instr_from_arr == 20 || instr_from_arr == 21) {
		strcpy(opsetg10, inst[instr_from_arr]);
		decode_opsetg10(opsetg10, bin_total);
	}
	else if (instr_from_arr == 22 || instr_from_arr == 23) { //swpb, sxt
		strcpy(opsetg11, inst[instr_from_arr]);
		decode_opsetg11(opsetg11, bin_total);
	}
	else if (instr_from_arr == 19) { //swap
		strcpy(opsetg12, inst[instr_from_arr]);
		decode_opsetg12(opsetg12, bin_total);
	}
	else if (instr_from_arr == 18) { //mov
		strcpy(opsetg23, inst[instr_from_arr]);
		decode_opsetg23(opsetg23, bin_total);
	}
	else if (instr_from_arr == 2) { //cex
		strcpy(opsetg3, inst[instr_from_arr]);
		decode_opsetg3(opsetg3, bin_total);
	}
	else if (instr_from_arr == 3) { //setpri
		strcpy(opsetg4, inst[instr_from_arr]);
		decode_opsetg4(opsetg4, bin_total);
	}
	else if (instr_from_arr == 4) { //svc
		strcpy(opsetg5, inst[instr_from_arr]);
		decode_opsetg5(opsetg5, bin_total);
	}
	else if (instr_from_arr == 5 || instr_from_arr == 6) { //setcc, clrcc
		strcpy(opsetg6, inst[instr_from_arr]);
		decode_opsetg6(opsetg6, bin_total);
	}
	else if (instr_from_arr == 24 || instr_from_arr == 25) { //ld, st
		strcpy(opsetg22, inst[instr_from_arr]);
		decode_opsetg22(opsetg22, bin_total);
	}
	else if (instr_from_arr ==  1) { //bra
		strcpy(opsetg1, inst[instr_from_arr]);
		decode_opsetg1(opsetg1, bin_total);
	}
	else if (instr_from_arr == 0) { //bra
		strcpy(opsetg2, inst[instr_from_arr]);
		decode_opsetg2(opsetg2, bin_total);
	}
	else if (instr_from_arr == 30 || instr_from_arr == 31) { //str, ldr
		strcpy(opsetg24, inst[instr_from_arr]);
		decode_opsetg24(opsetg24, bin_total);
	}
	else {
		printf("Not a valid instruction!");
	}

}