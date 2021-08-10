/**
* OperandG1.c: This file is used to decode the following operand: bra, bl
*  ECED 3403
* 21 August 09
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"

#define DEBUG
//converts input binary value to its decimal equivalent
int binary_to_decimal(char input[16]) {
	
	int decval=0;
	int arr_val, arr_count, hex_count;
	for (hex_count = 15,  arr_count = 0; (hex_count > -1) && (arr_count < 16); arr_count++, hex_count--) {
		arr_val = input[arr_count] - '0'; //converts from a character back to an integer
		decval = decval + arr_val*(pow(2, hex_count));
	}
	return decval;
}

//this function decodes the bra instruction using the input binary, address, and the input instruction
void decode_opsetg1(char input_instr[], char input_binary[16],  unsigned int address) {
#ifdef DEBUG
	printf("This is the input binary: %s \n", input_binary);

#endif // DEBUG


	//declare instruction to be decoded by end
	char decoded_instr[10];
	//declare signed bit
	char signed_bit = input_binary[6];
#ifdef DEBUG
	printf("This is the signed bit: %c \n", signed_bit);

#endif // DEBUG

	//extend signed bit to bits 10 - 15
	for (int i = 0; i < 6; i++) {
		input_binary[i] = signed_bit;
	}
	
#ifdef DEBUG
	printf("This is after the signed bit is extended: %s \n", input_binary);

#endif // DEBUG

	//shift result left by 1
	char shifted_instr[16];
	shifted_instr[15] = '0';
	
	int input_bit, shifted_bit;
	//store the offsetted instruction in shifted_instr array
	for (input_bit = 1, shifted_bit = 0; input_bit < 16; input_bit++, shifted_bit++) {
		shifted_instr[shifted_bit] = input_binary[input_bit];

	}

#ifdef DEBUG
	printf("This is the shifted instruction: %s \n", shifted_instr);

#endif // DEBUG

	//determine add or subtract
	
	char twos_arr[16];
	
	int offset_by; //need to add 1 to this value
	if (signed_bit == '1') {
		//bra has a negative value in the range -2(#FFFE) to -1024
		//find the twos complement to get the negative value
		for (int count = 0; count < 16; count++) {
			if (shifted_instr[count] == '0') {
				twos_arr[count] = '1';
			}
			else if (shifted_instr[count] == '1') {
				twos_arr[count] = '0';
			}
		}
#ifdef DEBUG
		printf("This is the twos array: %s", twos_arr);
#endif // DEBUG

		//convert the binary to a decimal value
		offset_by = -(binary_to_decimal(twos_arr)+1);
#ifdef DEBUG
		printf("This is the total offset: %d", offset_by);
#endif // DEBUG

	}	
	else if (signed_bit == '0') {
		//bra has a positive value in the range 0 (#0000) to 1022(#03FE)
		offset_by = binary_to_decimal(shifted_instr);

	}

	//add the result to the program counter
#ifdef DEBUG
	printf("address 1: %04x \n", address);

#endif // DEBUG

	unsigned int pc = address + 2;
#ifdef DEBUG
	printf("address 2 (offset): %04x \n", pc);
	printf("Offset: %d \n", offset_by);
#endif // DEBUG

	
	unsigned int branch_to = pc+offset_by;
	char target_addr[5];
	sprintf(target_addr, "#%04x", branch_to);

#ifdef DEBUG
	printf("address 3 (target address): %04x \n", branch_to);

#endif // DEBUG
	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, target_addr);

	append_file(decoded_instr);
	printf(decoded_instr);


}

//bl
void decode_opsetg2(char input_instr[], char input_binary[16],  unsigned int address) {
	//int address = 1000;
	//declare instruction to be decoded by end
	char decoded_instr[10];
	//declare signed bit
	char signed_bit = input_binary[3];


	//extend signed bit to bits 13 - 15
	for (int i = 0; i < 3; i++) {
		input_binary[i] = signed_bit;
	}

	//shift result left by 1
	char shifted_instr[16];
	shifted_instr[15] = '0';

	int input_bit, shifted_bit;
	//store the offsetted instruction in shifted_instr array
	for (input_bit = 1, shifted_bit = 0; input_bit < 16; input_bit++, shifted_bit++) {
		shifted_instr[shifted_bit] = input_binary[input_bit];

	}

	//determine add or subtract

	char twos_arr[16];

	int offset_by; //need to add 1 to this value
	if (signed_bit == '1') {
		//bra has a negative value in the range -2(#FFFE) to -1024
		//find the twos complement to get the negative value
		for (int count = 0; count < 16; count++) {
			if (shifted_instr[count] == '0') {
				twos_arr[count] = '1';
			}
			else if (shifted_instr[count] == '1') {
				twos_arr[count] = '0';
			}
		}

		//convert the binary to a decimal value
		offset_by = -(binary_to_decimal(twos_arr) + 1);
	}
	else if (signed_bit == '0') {
		//bra has a positive value in the range 0 (#0000) to 1022(#03FE)
		offset_by = binary_to_decimal(shifted_instr);

	}

	//add the result to the program counter
	printf("address 1: %04x \n", address);
	//fflush(stdout);
	unsigned int pc = address + 2;
	printf("address 2 (offset): %04x \n", pc);
	printf("Offset: %d \n", offset_by);
	//fflush(stdout);
	unsigned int branch_to = offset_by + pc;
	char target_addr[5];
	sprintf(target_addr, "#%04x", branch_to);
	printf("address 3 (target address): %04x \n", branch_to);
	//fflush(stdout);
	//construct instruction
	sprintf(decoded_instr, "%s %s", input_instr, target_addr);
	//puts("BRA was triggered.");

	append_file( decoded_instr);
	printf(decoded_instr);


}
