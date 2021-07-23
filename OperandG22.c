/**
* This file is used to decode the following operand: ld, st
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"
#include "Instr.h"


void decode_reg_g22(char r_bits[3], char* decoded_reg) {
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

char to_hex_g22(char bin_bits[4]) {
	const char* bin_possible_bits[] = { "000","001","010","011","100","101","110","111",0 };
	char hex_outputs[9] = { '0','1','2','3','4','5','6','7',0 };
	char hex_val;

	int counter = 0;

	//printf("G3 bin bits: %s", bin_bits);

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


void prpo_decision(char prpo[4], char reg[3], char* complete_reg) {

	char prpo_val = to_hex_g22(prpo);
	char temp[5];
	switch (prpo_val) {
	case '0':
		//do nothing
		strcpy(temp, reg);
	case '5':
		//pre-increment
		sprintf(temp, "+%s", reg);
	case '1':
		//post-increment
		sprintf(temp, "+%s", reg);
	case '6':
		//pre-decrement
		sprintf(temp, "-%s", reg);
	case '2':
		//post-decrement
		sprintf(temp, "%s-", reg);
	default:
		//invalid
		strcpy(temp, "inv");
		printf("Invalid entry!");
	}
	
	for (int i = 0; i < 4; i++) {
		complete_reg[i] = temp[i];
	}

}

/*
void w_or_b(char WB, char* decoded_wb) {
	char op[2];
	(WB == '0') ? (strcpy(op, ".w")) : (strcpy(op, ".b"));


	for (int i = 0; i < 2; ++i) {
		decoded_wb[i] = op[i];
	}


}
**/



//ldr, str
void decode_opsetg22(char input_instr[], char input_binary[16]) {

	//Store the Destination bits
	char D[4] = { input_binary[13],input_binary[14],input_binary[15],0 };
	//Store the SC bits
	char SC[4] = { input_binary[10],input_binary[11],input_binary[12],0 };
	//Store the word or byte bit.
	char WB = input_binary[9];

	//Store the PRPO, dec, inc bits
	char prpo_bits[4] = { input_binary[6], input_binary[7], input_binary[8], 0 };

	//Determine whether this is a store or a load command (ld=0, st=1)
	char st_ld = input_binary[5];

	//declare decoded vars
	char decoded_sreg[3];
	char decoded_dreg[3];
	char decoded_wb[3];
	char decoded_instr[13]; //ld.b +r1,r2(0) - 13 characters needed.

	char complete_sreg[4]; //with prpo
	char complete_dreg[4]; //with prpo

	//store the destination register
	decode_reg_g22(D, decoded_dreg);

	//store the source register
	decode_reg_g22(SC, decoded_sreg);


	switch (st_ld) {
	case '0':
		// this is a ld instruction. ergo, the src register is modified
		prpo_decision(prpo_bits, decoded_sreg, complete_sreg);
		strcpy(complete_dreg, decoded_dreg);
		break;

	case '1':
		//this is a st instruction. ergo, the destination register is modified.
		prpo_decision(prpo_bits, decoded_dreg, complete_dreg);
		strcpy(complete_sreg, decoded_sreg);
		break;
	default:
		//there is an error. must be 0 or 1.
		printf("There is an error in the instruction!");
	}

	//word or byte instruction
	w_or_b(WB, decoded_wb);
	strcat(input_instr, decoded_wb);


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, complete_sreg, complete_dreg);

	printf(decoded_instr);


}