/**
* This file is used to decode the following operands: ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, BIT, BIC, BIS. 
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"


//decode constant
void decode_const(char sc_bits[3], char* output) {
	const char *sc_possible_bits[] = { "000","001","010","011","100","101","110","111" };
	const char *c_outputs[] = { "#00","#01","#02","#04","#08","#16","#32","#-1" };
	char const_val[3];

	int counter=0;

	while (strcmp(sc_bits, sc_possible_bits[counter]) != 0 && counter < 9) {
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		strcpy(const_val, c_outputs[counter]);
	}
	/**
	switch (sc_bits) {
	case "000":
		c = "#00";
		break;
	case "001":
		c = "#01";
		break;
	case "010":
		c = "#02";
		break;
	case "011":
		c = "#04";
		break;
	case "100":
		c = "#08";
		break;
	case "101":
		c = "#16";
		break;
	case "110":
		c = "#32";
		break;
	case "111":
		c = "#-1";
		break;
	default:
		c = "Err");
		break;
	};
	*/
	for (int i = 0; i < 3; i++) {
		output[i] = const_val[i];
	}

}
/**
char decode_const[3](char[3] sc_bits) {
	char[3] c;
	switch (sc_bits) {
	case "000":
		c ="#00";
	case "001":
		c="#01";
	case "010":
		c = "#02";
	case "011":
		c = "#04";
	case "100":
		c = "#08";
	case "101":
		c = "#16";
	case "110":
		c = "#32";
	case "111":
		c = "#-1";
	default:
		c = "Err");
	};
	return c;

}
**/
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
	/*
	char *reg[2];
	switch (r_bits) {
	case "000":
		reg = "R0";
		break;
	case "001":
		reg = "R1";
		break;
	case "010":
		reg = "R2";
		break;
	case "011":
		reg = "R3";
		break;
	case "100":
		reg = "R4";
		break;
	case "101":
		reg = "R5";
		break;
	case "110":
		reg = "R6";
		break;
	case "111":
		reg = "R7";
		break;
	default:
		reg = "Er";
		break;
	};
	*/

	for (int i = 0; i < 2; i++) {
		decoded_reg[i] = reg_val[i];
	}

}

/*
//decode register
char decode_reg[2](char[3] r_bits) {
	char[2] r;
	switch (r_bits) {
	case "000":
		reg= "R0";
	case "001":
		reg = "R1";
	case "010":
		reg = "R2";
	case "011":
		reg = "R3";
	case "100":
		reg = "R4";
	case "101":
		reg = "R5";
	case "110":
		reg = "R6";
	case "111":
		reg = "R7";
	default:
		reg = "Er";
	};
	return r;
}
**/
void w_or_b(char WB, char* decoded_wb) {
	char op[2];
	(WB == '0') ? (strcpy(op, ".w")) : (strcpy(op, ".b"));

	/**
	switch (WB) {
	case("0"):
		sub = ".w";
		break;
	case("1"):
		sub = ".b";
		break;
	default:
		sub = "er";
		break;
	}
	**/

	for (int i = 0; i < 2; ++i) {
		decoded_wb[i] = op[i];
	}


}

void decode_opset1(char input_instr[], char input_binary[16]) {

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
	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_sc, decoded_dreg);
	
	printf(decoded_instr); 


}

//group 11: swpb/sxt
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

	printf(decoded_instr);


}


//group 12: swap
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

	printf(decoded_instr);


}


//group 13: mov. example: mov.b Rsource,Rdest
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


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_sreg, decoded_dreg);

	printf(decoded_instr);


}