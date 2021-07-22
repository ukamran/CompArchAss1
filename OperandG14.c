/**
* This file is used to decode the following operand: bra, bl
* 
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"


void decode_reg(char r_bits[3], char* decoded_reg) {
	const char* rc_possible_bits[] = { "000","001","010","011","100","101","110","111" };
	const char* r_outputs[] = { "R0","R1","R2","R3","R4","R5","R6","R7" };
	char reg_val[2];

	int counter = 0;

	while (strcmp(r_bits, rc_possible_bits[counter]) != 0 && counter < 9) {
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		strcpy(reg_val, r_outputs[counter]);
	}


	for (int i = 0; i < 2; i++) {
		decoded_reg[i] = reg_val[i];
	}

}
void w_or_b(char WB, char* decoded_wb) {
	char op[2];
	(WB == '0') ? (strcpy(op, ".w")) : (strcpy(op, ".b"));


	for (int i = 0; i < 2; ++i) {
		decoded_wb[i] = op[i];
	}


}
char to_hex_g3(char bin_bits[4]) {
	const char* bin_possible_bits[] = { "000","001","010","011","100","101","110","111",0 };
	char hex_outputs[9] = { '0','1','2','3','4','5','6','7',0 };
	char hex_val;

	int counter = 0;

	printf("G3 bin bits: %s", bin_bits);

	while (strcmp(bin_bits, bin_possible_bits[counter]) != 0 && counter < 9) {
		printf(bin_possible_bits[counter]);
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		hex_val = hex_outputs[counter];
	}
	return hex_val;
}

//decode constant
char to_hex_4bits(char bin_bits[5]) {
	const char* bin_possible_bits[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
										"1000","1001","1010","1011","1100","1101","1110","1111",0 };
	char hex_outputs[17] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',0 };
	char hex_val;

	int counter = 0;

	printf("Bin bits: %s", bin_bits);

	while (strcmp(bin_bits, bin_possible_bits[counter]) != 0 && counter < 17) {
		printf(bin_possible_bits[counter]);
		counter++;
	}
	if (counter >= 16) {
		printf("There is an error");
	}
	else {
		hex_val = hex_outputs[counter];
	}
	return hex_val;
}

//ldr, str
void decode_opsetg14(char input_instr[], char input_binary[16]) {

	//Store the Destination bits
	char D[4] = { input_binary[13],input_binary[14],input_binary[15],0 };
	//Store the SC bits
	char SC[4] = { input_binary[10],input_binary[11],input_binary[12],0 };
	//Store the word or byte bit.
	char WB = input_binary[9];

	char offset[7] = { input_binary[2],input_binary[3] ,input_binary[4] ,input_binary[5] ,input_binary[6],input_binary[7],0 };

	//declare decoded vars
	char decoded_dreg[3];
	char decoded_sreg[3];
	char decoded_wb[2];
	char decoded_instr[13];


	//store the destination register
	decode_reg(D, decoded_dreg);

	//store the source register
	decode_reg(SC, decoded_sreg);

	//word or byte instruction
	w_or_b(WB, decoded_wb);
	strcat(input_instr, decoded_wb);


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_sreg, decoded_dreg);

	printf(decoded_instr);


}