/**
* This file is used to decode the following operands: LDR & STR
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "Output_File.h"
#include "Chk_SRec.h"

int binary_to_decimal_7bit(char input[7]) {

	int decval = 0; //decimal value
	int arr_val, arr_count, power_count;
	for (power_count = 6, arr_count = 0; (power_count > -1) && (arr_count < 7); arr_count++, power_count--) {
		arr_val = input[arr_count] - '0';
		decval = decval + arr_val * (pow(2, power_count));
	}
	return decval;
}



//ldr str instructions
void decode_opsetg24(char input_instr[], char input_binary[16],  unsigned int address) {

	//Determine if this is an ldr (0) or str (1) instruction
	char ldrstr = input_binary[1];
	
	//Store the word or byte bit.
	char WB = input_binary[9];

	//Store the SC bits
	char SC[3] = { input_binary[10],input_binary[11],input_binary[12] };

	//Store the Destination bits
	char D[3] = { input_binary[13],input_binary[14],input_binary[15] };
	
	//Store the offset bits
	char offset[7] = { input_binary[2],input_binary[3],input_binary[4],input_binary[5],input_binary[6],
						input_binary[7], input_binary[8] };

	//Store the signed bit
	char signed_bit = input_binary[2];

	char twos_arr[7];

	int offset_by; //need to add 1 to this value
	if (signed_bit == '1') {
		//ldr has a negative value in the range -64 to -1
		//find the twos complement to get the negative value
		for (int count = 0; count < 7; count++) {
			if (offset[count] == '0') {
				twos_arr[count] = '1';
			}
			else if (offset[count] == '1') {
				twos_arr[count] = '0';
			}
		}

		//convert the binary to a decimal value
		offset_by = -(binary_to_decimal_7bit(twos_arr) + 1); //need to add 1 to complete twos notation
	}
	else if (signed_bit == '0') {
		//bra has a positive value in the range 0  to 64
		offset_by = binary_to_decimal_7bit(offset);
	}
	
	char offset_char = offset_by + '0'; //convert to a character
	char offset_instr[2] = { '#',offset_char };

	//declare decoded vars
	char decoded_sc[3];
	char decoded_dreg[3];
	char decoded_wb[2];
	char decoded_instr[15];

	//store the source register
	decode_reg(SC, decoded_sc);
	
	//store the destination register
	decode_reg(D, decoded_dreg);

	//store the word or byte value
	w_or_b(WB, decoded_wb);

	strcat(input_instr, decoded_wb);

	//if 0, ldr. if 1, it's str.
	if (ldrstr == '0') {
		//construct instruction
		sprintf(decoded_instr, "%s %s,%s,%s", input_instr, decoded_sc,offset_instr, decoded_dreg);
	}
	else if (ldrstr == '1') {
		sprintf(decoded_instr, "%s %s,%s,%s", input_instr, decoded_sc, decoded_dreg, offset_instr);
	}
	
	append_file(decoded_instr);
	printf(decoded_instr);


}


