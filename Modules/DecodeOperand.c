/**
* DecodeOperand.c: This file is used to decode the following operands:  
   Group 1: ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, BIT, BIC, BIS. 
   Group 2: SWPB, SXT
   group 12: swap
   group 13: mov
*  ECED 3403
*  21 August 09
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"
#include "Instr.h"


//decode constant
void decode_const(char sc_bits[3], char* output) {

	//map the source or constant possible bits to the constant outputs
	const char *sc_possible_bits[] = { "000","001","010","011","100","101","110","111" };
	const char *c_outputs[] = { "#00","#01","#02","#04","#08","#16","#32","#-1" };
	char const_val[3];

	int counter=0;

	//retrieve the correct map location
	while (strcmp(sc_bits, sc_possible_bits[counter]) != 0 && counter < 9) {
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		strcpy(const_val, c_outputs[counter]);
	}
	//copy the constant value to the output register
	for (int i = 0; i < 3; i++) {
		output[i] = const_val[i];
	}

}
void decode_reg(char r_bits[3], char* decoded_reg) {
	//map the register possible bits to the register outputs

	const char* rc_possible_bits[] = { "000","001","010","011","100","101","110","111" };
	const char* r_outputs[] = { "R0","R1","R2","R3","R4","R5","R6","R7" };
	char reg_val[2];

	int counter = 0;
	//retrieve the correct map location

	while (strcmp(r_bits, rc_possible_bits[counter]) != 0 && counter < 9) {
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		strcpy(reg_val, r_outputs[counter]);
	}
	//copy the constant value to the output register

	for (int i = 0; i < 2; i++) {
		decoded_reg[i] = reg_val[i];
	}

	//null terminate to prevent extraneous characters
	decoded_reg[2] = 0;


}

// determine whether it is a word or a byte
void w_or_b(char WB, char* decoded_wb) {
	char op[2];

	//ternary operator that copies .w or .b depending on if the WB value is 0 or 1
	(WB == '0') ? (strcpy(op, ".w")) : (strcpy(op, ".b"));

	//copy the output value into the array
	for (int i = 0; i < 2; ++i) {
		decoded_wb[i] = op[i];
	}


}

//this function is used to decode the following operands:  ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, BIT, BIC, BIS. 
//it utilizes the input instruction and the input binary as provided
void decode_opset1(char input_instr[], char input_binary[16]) {

	//printf("%s\n",input_binary);
	// Store the register or constant bit.
	char RC = input_binary[8];

	//Store the word or byte bit.
	char WB = input_binary[9];

	//Store the SC bits
	char SC[3] = { input_binary[10],input_binary[11],input_binary[12] };

	//Store the Destination bits
	char D[3] = { input_binary[13],input_binary[14],input_binary[15] };

	//declare decoded vars
	char decoded_sc[3];
	char decoded_dreg[3];
	char decoded_wb[2];
	char decoded_instr[13];

	//store the register or constant
	if (RC=='1') {
		decode_const(SC, decoded_sc);
	}
	else {
		decode_reg(SC, decoded_sc);
	}

	//store the destination register
	decode_reg(D, decoded_dreg);


	w_or_b(WB, decoded_wb);

	strcat(input_instr, decoded_wb);

	//null terminates to prevent extraneous characters
	if (input_instr[5] == 'w' || input_instr[5] == 'b') {
		input_instr[6] = 0;
	}
	else {
		input_instr[5] = 0;
	}
	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_sc, decoded_dreg);
	
	append_file(decoded_instr);
	printf(decoded_instr);


}

//group 11: decodes swpb/sxt
//it utilizes the input instruction and the input binary as provided
void decode_opsetg11(char input_instr[], char input_binary[16]) {

	//Store the Destination bits
	char D[4] = { input_binary[13],input_binary[14],input_binary[15],0 };

	//declare decoded vars
	char decoded_dreg[3];
	char decoded_instr[13];


	//store the destination register
	decode_reg(D, decoded_dreg);

	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, decoded_dreg);

	append_file(decoded_instr);
	printf(decoded_instr);


}


//group 12: decodes swap
//it utilizes the input instruction and the input binary as provided
void decode_opsetg12(char input_instr[], char input_binary[16]) {

	//Store the Destination bits
	char D[4] = { input_binary[13],input_binary[14],input_binary[15],0 };
	//Store the SC bits
	char SC[4] = { input_binary[10],input_binary[11],input_binary[12],0 };

	//declare decoded vars
	char decoded_dreg[3];
	char decoded_sreg[3];
	char decoded_instr[13];


	//store the destination register
	decode_reg(D, decoded_dreg);

	//store the source register
	decode_reg(SC, decoded_sreg);


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_sreg, decoded_dreg);

	append_file(decoded_instr);
	printf(decoded_instr);


}


//group 13: decodes mov. example: mov.b Rsource,Rdest
//it utilizes the input instruction and the input binary as provided
void decode_opsetg23(char input_instr[], char input_binary[16]) {

	//Store the Destination bits
	char D[4] = { input_binary[13],input_binary[14],input_binary[15],0 };
	//Store the SC bits
	char SC[4] = { input_binary[10],input_binary[11],input_binary[12],0 };
	//Store the word or byte bit.
	char WB = input_binary[9];

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
	input_instr[5] = 0;

	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_sreg, decoded_dreg);

	append_file(decoded_instr);
	printf(decoded_instr);

}


