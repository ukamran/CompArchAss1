/**
* OperandG24.c: This file is used to decode the following operands: ld, st
* ECED 3403
* 21 August 09
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"
#include "Instr.h"

//this function converts input register bits to their register equivalent
void decode_reg_g22(char r_bits[3], char* decoded_reg) {
	const char* rc_possible_bits[] = { "000","001","010","011","100","101","110","111",0 }; //possible input bits
	const char* r_outputs[] = { "R0","R1","R2","R3","R4","R5","R6","R7",0 }; //possible output register values mapped to their equivalent input bits
	char reg_val[2];

	int counter = 0;

	//compare the input value to the rc_possible_bits. increment until strcmp returns 0, indicating that the input and rc_possible_bits value is the same
	while (strcmp(r_bits, rc_possible_bits[counter]) != 0 && counter < 9) {
		counter++;
	}
	//counter can't be greater than 8
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		//copy the register value into the reg_val character array
		strcpy(reg_val, r_outputs[counter]);
	}


	for (int i = 0; i < 3; i++) {
		//copy the register value into the output array
		decoded_reg[i] = reg_val[i];
	}
	//set the 3rd value in the character array to 0 in order to prevent excess characters
	decoded_reg[2] = 0;

}

//this function converts input bits to their hex equivalent
char to_hex_g22(char bin_bits[4]) {
	//null terminate
	bin_bits[3] = 0;
	//map the binary bits to their equivalent hex values
	const char* bin_possible_bits[] = { "000","001","010","011","100","101","110","111",0};
	char hex_outputs[9] = { '0','1','2','3','4','5','6','7',0};
	char hex_val;

	int counter = 0;

	//compare the input to binary bits to the possible binary bits array. 
	//while loop terminates upon the strcmp function returning 0 
	while (strcmp(bin_bits, bin_possible_bits[counter]) != 0 && counter < 9) {
		printf(bin_possible_bits[counter]);
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error\n");
	}
	else {
		//select the hex value based on the counter from the hex_outputs array
		hex_val = hex_outputs[counter];
	}
	return hex_val;
}

//this function returns the appropriate post or pre increment or decrement with the appropriate register
void prpo_decision(char prpo[4], char reg[3], char* complete_reg) {

	//get the hex value from the input encoded bits
	char prpo_val = to_hex_g22(prpo);
	char temp[5]; //temporary array
	int null_val=2; //default null terminator location

	//switch case based on the prpo hex value
	switch (prpo_val) {
	case '0':
		//do nothing
		strcpy(temp, reg);
		break;
	case '5':
		//pre-increment
		null_val = 3;
		sprintf(temp, "+%s", reg);
		break;
	case '1':
		//post-increment
		null_val = 3;
		sprintf(temp, "%s+", reg);
		break;
	case '6':
		//pre-decrement
		null_val = 3;
		sprintf(temp, "-%s", reg);
		break;
	case '2':
		//post-decrement
		null_val = 3;
		sprintf(temp, "%s-", reg);
		break;
	default:
		printf("Invalid prpo \n");
		strcpy(temp, "inv");
		break;
	}
	
	//copy the register character array stored in temp into the output character array.
	//null terminate based on the null_val counter
	for (int i = 0; i < 4; i++) {
		complete_reg[i] = temp[i];
	}
	complete_reg[null_val] = 0;
}




//This function decodes ld and st instructions
void decode_opsetg22(char input_instr[], char input_binary[16], unsigned int address) {

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
	decoded_dreg[2] = 0;
	printf("This is the decoded D Register %s\n", decoded_dreg);
	//store the source register
	decode_reg_g22(SC, decoded_sreg);
	printf("This is the decoded S Register %s\n", decoded_sreg);
	decoded_sreg[2] = 0;

	//the switch case determines, based on the 5th input binary value, whether it is an st or an ld.
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
	decoded_wb[2] = 0;
	w_or_b(WB, decoded_wb);
	strcat(input_instr, decoded_wb);


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, complete_sreg, complete_dreg);

	append_file(decoded_instr);
	printf(decoded_instr);


}