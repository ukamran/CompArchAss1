/**
* OperandG6.c: 
* Group 6: This file is used to decode the following operand: setcc, clrcc.
* ECED 3403
*  21 August 09
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"




//decodes setcc clrcc using input instruction, input binary, and the address values in parameters
void decode_opsetg6(char input_instr[], char input_binary[16], unsigned int address) {

	//Store the bits
	char v = input_binary[11];
	char slp = input_binary[12];
	char n = input_binary[13];
	char z = input_binary[14];
	char c = input_binary[15];

	//declare output bits
	char output_v;
	char output_slp;
	char output_n;
	char output_z;
	char output_c;
	char output[6];

	char decoded_instr[12];

	int counter = 0;

	//construct the instruction based on the values present in vnzsc bits
	if (v == '1') {
		output_v = 'V';
		output[counter] = output_v;
		counter++;
	}

	if (slp == '1') {
		output_slp = 'S';
		output[counter] = output_slp;
		counter++;
	}

	if (n == '1') {
		output_n = 'N';
		output[counter] = output_n;
		counter++;
	}

	if (z == '1') {
		output_z = 'Z';
		output[counter] = output_z;
		counter++;
	}

	if (c == '1') {
		output_c = 'C';
		output[counter] = output_c;
		counter++;
	}

	//null terminate the output
	output[counter] = 0;
	
	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, output);

	append_file(decoded_instr);
	printf(decoded_instr);

}

