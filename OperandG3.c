/**
* This file is used to decode the following operand: cex, setpri, svc.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"


//decode constant
void decode_conditionals(char bin_bits[5], char* decoded_cond) {
	const char* bin_possible_bits[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
										"1000","1001","1010","1011","1100","1101","1110","1111",0 };
	const char* cond_outputs[] = { "EQ","NE","CS","CC","MI","PL", "VS","VC","HI","LS","GF","LT","GT","LE","TR","F",0};
	char cond_val[3];

	int counter = 0;

	printf("Bin bits: %s", bin_bits);

	while (strcmp(bin_bits, bin_possible_bits[counter]) != 0 && counter < 9) {
		counter++;
	}
	if (counter >= 8) {
		printf("There is an error");
	}
	else {
		strcpy(cond_val, cond_outputs[counter]);
	}


	for (int i = 0; i < 2; i++) {
		decoded_cond[i] = cond_val[i];
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


//cex instruction
void decode_opsetg3(char input_instr[], char input_binary[16]) {

	//Store the byte
	char cond_bits[5] = { input_binary[6],input_binary[7],input_binary[8],input_binary[9],0 };
	char true_bits[4] = { input_binary[10], input_binary[11], input_binary[12],0 };
	char false_bits[4] = { input_binary[13], input_binary[14], input_binary[15],0 };

	//declare decoded vars

	char decoded_conds[3];
	char decoded_instr[13];


	//store the conditionals register
	decode_conditionals(cond_bits, decoded_conds);

	
	//inscribe proper format cex cond,#(0-7),#(0-7)
	char tf_arr[6] = { '#', to_hex_g3(true_bits),',','#', to_hex_g3(false_bits), 0};


	//construct instruction
	sprintf(decoded_instr, "%s %s,%s", input_instr, decoded_conds, tf_arr);

	printf(decoded_instr);


}

//setpri
void decode_opsetg4(char input_instr[], char input_binary[16]) {

	//Store the byte
	char pr_bits[4] = { input_binary[13], input_binary[14], input_binary[15],0 };

	//declare decoded vars
	char decoded_instr[10];


	//inscribe proper format cex cond,#(0-7),#(0-7)
	char setpri_arr[3] = { '#', to_hex_g3(pr_bits), 0 };


	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, setpri_arr);

	printf(decoded_instr);
}

//svc
void decode_opsetg5(char input_instr[], char input_binary[16]) {

	//Store the byte
	char sa_bits[5] = { input_binary[12], input_binary[13], input_binary[14], input_binary[15],0 };

	//declare decoded vars
	char decoded_instr[10];


	//inscribe proper format svc #(0-F)
	char svc_arr[3] = { '#', to_hex_4bits(sa_bits), 0 };


	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, svc_arr);

	printf(decoded_instr);

}

