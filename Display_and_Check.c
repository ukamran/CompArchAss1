/*
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
 - 14 May 2021
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Chk_SRec.h"
#include "Output_File.h"
#include "Instr.h"

#define DISPLAY_BYTE /* Remove comments '//' to display contents of S1 and S9 records */
int hextodc(char* hex) {
	int y = 0;
	int dec = 0;
	int x, i;
	for (i = strlen(hex) - 1; i >= 0; --i){
		if (hex[i] >= '0' && hex[i] <= '9') {
			x = hex[i] - '0';
		}
		else {
			x = hex[i] - 'A' + 10;
		}
	dec = dec + x * pow(16, y);// converting hexadecimal to integer value ++y;
	}
return dec;
}

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

//added this just now
unsigned int arr_count;
unsigned int counter;
unsigned int addr; 

unsigned int s1_arr[20];
unsigned int s1_arrass[2];
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
		printf("This is the byte: %d", byte);
		//char parsedRecord[] = "Cool.";
		//output_file(byte);
		chksum += CHAR_MASK(byte);
		pos += 2;
	}
	break;
case '1': /* Data (Instruction or data) record */
	/* Print first address and bytes */
	arr_count = 0;
	counter = 0;

	printf("Address: %04x: ", address);
	interim_address = address;
	for (i = 0; i <= length; i++)
	{
		sscanf_s(&srec[pos], "%2x", &byte);
#ifdef DISPLAY_BYTE
		//printf("This is for S1: %02x ", byte);
#endif
		chksum += CHAR_MASK(byte);

		if (((pos % 4) == 0) && (pos!=8)) {
			//decodeAssembly(s1_arr);
			unsigned int loop;
			char high[2];
			char low[2];
			//for (loop = 0; loop < 2; loop += 1) {
				//printf("High: %02x ,", s1_arrass[1]);
				//printf("Low: %02x ,", s1_arrass[0]);
				//printf(high, "%02x", s1_arrass[1]);
				//sprintf(low, "%02x", s1_arrass[0]);
				//printf("High: %c", high);
				//printf();
				//printf("Low: %c", low);
				//printf();
				//int high_int = high - '0';
				//int low_int = low - '0';

				//printf("High int: %d", high_int);
				//printf("Low int: %d", low_int);

				//printf("First char high: ");
				//printf(high[0]);
				//printf("Second char high: ");
				//printf(high[1]);
				//printf("Third char low: ");
				//printf(low[0]);

				//decode_assembly(s1_arrass[1], s1_arrass[0]);
				//printf("Address: #%04x \n", interim_address);
				decode_assembly(s1_arrass[1], s1_arrass[0], interim_address);
				
			//}
			counter = 0;
		}
		//my code
		s1_arrass[counter] = byte;
		counter += 1;
		pos += 2;
		interim_address += 2;

		//s1_arr[arr_count] = byte;
		//arr_count += 1;
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