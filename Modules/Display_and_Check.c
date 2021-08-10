/*
* 
* This file has been modified from the original file provided by Dr Hughes.
 Display_fields_and_check
 - Display contents of each SRecord field
 - Determine checksum: length + addr-high + addr-low + data-bytes + chksum-byte
 - Checksum = 0xFF - valid
 - Notes:
   - Header is one character in srec[0]
   - Type is one character in srec[1]
   - Length is a byte represented by two chars in srec (srec[2] and srec[3])
     Each char represents a nibble
	 The srecord is a character file, using characters to represent nibbles (0..F); a pair
	 of characters represent a byte ("00" to "FF"). Bytes can be read using sscanf() with
	 format %2x.
	 The srecord format means control characters (character pairs "00" to "1F") are not 
	 misinterpreted as actual control characters, such as carriage return, line feed, tabs,
	 NUL, and form feed.
   - Ah and Al are a byte in length (two chars in srec): srec[4 & 5] and srec[6 & 7]
     Address <- Ah << 8 | Al
	 Address is stored in big-endian format
   - Data bytes are represented by two chars in srec starting at srec[8 & 9]
 - ECED 3403
 - 09 August 2021
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Chk_SRec.h"
#include "Output_File.h"
#include "Instr.h"

#define DISPLAY_BYTE /* Remove comments '//' to display contents of S1 and S9 records */


void display_and_check_srec(char* srec)
{
/*
 - Scan record for S-Record fields
 - Extract S-Records using type (0, 1, and 9)
 - Calc checksum: length + ah + al + data bytes
 */
unsigned int length;
unsigned int ah, al, address;
unsigned int interim_address;
unsigned int byte;
unsigned int chksum;
unsigned int pos;
unsigned int i;

unsigned int arr_count;
unsigned int counter;
unsigned int addr; 

unsigned int s1_arrass[2];
unsigned int arr[40];
unsigned int address_arr[40];


char filename[100]; //filename array declaration
char org_arr[10]; //origin


/* Check for 'S' (srec[0]) */
if (srec[0] != 'S')
{
	printf("Invalid header: >>%c<< - record ignored\n\n", srec[0]);
	return;
}

/* 
 - Header correct, extract common elements 
 - sscanf() requires arguments of type unsigned int, whether it is a char or pairs of chars 
*/
sscanf_s(&srec[2], "%2x%2x%2x", &length, &ah, &al);

if (length > MAX_SREC_DATA)
{
	printf("Invalid length: %d\n\n", length);
	return;
}

address = (ah << 8) | al;
printf("Header: %c Type: %c Length: %d Address: %04x\n",
		srec[0], srec[1], length, address);

chksum = length + ah + al;
length -= 3; /* Length, address and checksum bytes already handled */
pos = 8;     /* First byte in data (position 8 in srec[] */

/* Read data bytes */
switch (srec[1])
{

case '0': /* Source filename */
	/* Print filename plus checksum byte */
	for (i = 0; i <= length; i++)
	{

		sscanf_s(&srec[pos], "%2x", &byte);
		char bytechar = byte;
		filename[i] = bytechar; //store the filename
		chksum += CHAR_MASK(byte);
		pos += 2;
	}

	filename[i - 1] = '\0'; //null terminate to avoid special characters at the end
	create_file(filename, length); //create the file with the provided name

	break;

case '1': /* Data (Instruction or data) record */
	/* Print first address and bytes */
	
	arr_count = 0;
	counter = 0;
	int max_length = length;
	sprintf(org_arr, "ORG #%04x", address); //store the address in a string array as formatted to the left
	append_file(org_arr); //add the address to the file

	interim_address = address;
	unsigned int final_pos = pos + (length - 3) * 2;


	for (i = 0; i <= length; i++)
	{
		sscanf_s(&srec[pos], "%2x", &byte);
#ifdef DISPLAY_BYTE
		//printf("This is for S1: %02x \n", byte);
#endif
		chksum += CHAR_MASK(byte);
			
		address_arr[i] = interim_address; //store the address in array
		arr[i] = byte; //store the byte in array

		counter += 1;
		interim_address += 1;
		pos += 2; //move two spots up to read the next pertinent encoded instruction 
		arr_count += 1; //increment the array


	}
	
	//decode each valid instruction in the array. feed the high byte, low byte, and address to the decode_assembly function.
	int count_up = 0;	
	
	for (count_up = 0; count_up < i; count_up++) {
		if ((count_up % 2) == 0 && (count_up != i - 1)) {
			decode_assembly(arr[count_up +1], arr[count_up], address_arr[count_up]);
		}
		count_up++;
	}
	break;
case '9': /* Starting address record */
	printf("Starting address: %04x", address);
	sscanf_s(&srec[pos], "%2x", &byte);
#ifdef DISPLAY_BYTE
	printf("%02x ", byte);
#endif
	chksum += CHAR_MASK(byte);
	break;

default:
	printf("Invalid type: >>%c<<\n\n", srec[1]);
	return;
}

printf("\nChksum: %02x\n", CHAR_MASK(chksum));

if (CHAR_MASK(chksum) == 0xFF)
	printf("Valid checksum\n\n");
else
	printf("Invalid checksum\n\n");
}