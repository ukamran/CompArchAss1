/**
* OperandG10.c: This file is used to decode the following operands: 
* Group 10:SRA,RRC.
* ECED 3403
*  21 August 09
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"


//determine whether there is a word or a byte
void w_or_bg10(char WB, char* decoded_wb) {
	char op[2];
	(WB == '0') ? (strcpy(op, ".w")) : (strcpy(op, ".b"));

	for (int i = 0; i < 2; ++i) {
		decoded_wb[i] = op[i];
	}
}

//select register
void decode_regg10(char r_bits[4], char* decoded_reg) {

	const char* rc_possible_bits[] = { "000","001","010","011","100","101","110","111",0};
	const char* r_outputs[] = { "R0","R1","R2","R3","R4","R5","R6","R7",0};
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



//group 10: sra, rrc decoded here
//it utilizes the input instruction, the input binary, and the addresse as seen in params
void decode_opsetg10(char input_instr[], char input_binary[16],  unsigned int address) {

	//Store the word or byte bit.
	char WBg10 = input_binary[9];

	//Store the Destination bits
	char D[4] = { input_binary[13],input_binary[14],input_binary[15],0 };

	//declare decoded vars

	char decoded_dregg10[3];
	char decoded_instr[9]; //sra.b r0 is 8 + 1 for null terminated value
	char decoded_wb[3];

	//determine word or byte and concatenate with instruction
	w_or_bg10(WBg10, decoded_wb);
	strcat(input_instr, decoded_wb);
	input_instr[5] = 0;
	//store the destination register
	decode_regg10(D, decoded_dregg10);


	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, decoded_dregg10);

	append_file( decoded_instr);
	printf(decoded_instr);


}


