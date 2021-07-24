/**
* This file is used to decode the following operands: MOVL, MOVLZ, MOVLS, MOVH.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"


//decode constant
char to_hex(char bin_bits[5]) {
	const char* bin_possible_bits[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
										"1000","1001","1010","1011","1100","1101","1110","1111",0};
	char hex_outputs[17] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',0};
	char hex_val;

	int counter = 0;

	//printf("Bin bits: %s", bin_bits);

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

void decode_regg13(char r_bits[3], char* decoded_reg) {
	const char* rc_possible_bits[] = { "000","001","010","011","100","101","110","111", 0 };
	const char* r_outputs[] = { "R0","R1","R2","R3","R4","R5","R6","R7",0 };
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




void decode_opsetg13(char input_instr[], char input_binary[16], char filename[]) {

	//Store the byte
	char byte_instr_one[5] = { input_binary[5],input_binary[6],input_binary[7],input_binary[8],0 };
	char byte_instr_two[5]= {input_binary[9], input_binary[10], input_binary[11], input_binary[12],0 };

	char hex_arr[3] = { '#', to_hex(byte_instr_one), to_hex(byte_instr_two) };
	//Store the Destination bits
	char D[3] = { input_binary[13],input_binary[14],input_binary[15] };

	//declare decoded vars
	
	char decoded_dregg13[3];
	char decoded_instr[13];


	//store the destination register
	decode_regg13(D, decoded_dregg13);


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, hex_arr, decoded_dregg13);

	append_file(filename, decoded_instr);
	printf(decoded_instr);


}




