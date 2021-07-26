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

/*
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
**/
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

unsigned int s1_arrass[2];
unsigned int arr[40];
unsigned int address_arr[40];


char filename[100];

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
		//printf("This is the byte: %d", byte);
		char bytechar = byte;
		filename[i] = bytechar;
		//printf("%c", bytechar);
		//char parsedRecord[] = "Cool.";
		//output_file(byte);
		chksum += CHAR_MASK(byte);
		pos += 2;
	}

	filename[i - 1] = '\0'; //null terminate to avoid special characters at the end
	/*
	int counter = 0;
	while (filename_temp[counter] != '\0') {
		counter++;
	}
	printf("Length: %d \n", counter);
	for (int i = 0; i < (counter + 1); i++) {
		printf("%c", filename_temp[i]);
	}
	*/
	printf(" This is the filename in S0: %s", filename);
	create_file(filename, length);

	break;

case '1': /* Data (Instruction or data) record */
	/* Print first address and bytes */
	//printf(" This is the filename in S1 at start: %s", filename);

	arr_count = 0;
	counter = 0;
	int max_length = length;
	printf("Address: %04x: ", address);
	interim_address = address;
	unsigned int final_pos = pos + (length - 3) * 2;


	for (i = 0; i <= length; i++)
	{
		sscanf_s(&srec[pos], "%2x", &byte);
#ifdef DISPLAY_BYTE
		//printf("This is for S1: %02x \n", byte);
#endif
		chksum += CHAR_MASK(byte);
		/**
			printf("This is the array: %2x\n", arr[arr_count]);

			if ((i%2)==0) {
				counter = 0;
			}
			s1_arrass[counter] = byte;

			printf("Array counter: %d\n", arr_count);
			printf("i: %d, length: %d\n", i, length);

			if (((pos % 4) == 0) && (pos!=8)) {
				//decodeAssembly(s1_arr);
				printf("pos: %d\n", pos);
				unsigned int loop;
				char high[2];
				char low[2];
				//for (loop = 0; loop < 2; loop += 1) {
					printf("High: %02x ,", s1_arrass[1]);
					printf("Low: %02x ,", s1_arrass[0]);
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
					printf("Address: #%04x \n", interim_address);
					//decode_assembly(s1_arrass[1], s1_arrass[0], interim_address, filename);
					counter = 0;
				//}
				}
		**/
		//my code
		address_arr[i] = interim_address;
		arr[i] = byte;

		counter += 1;

		interim_address += 1;
		printf("%d \n",interim_address);
		pos += 2;

		//s1_arr[arr_count] = byte;
		arr_count += 1;


	}
	int count_up = 0;
	int count_up_h = 1;

	//decode_assembly(arr[1], arr[0], 1000, filename);
	//decode_assembly(arr[3], arr[2], 1000, filename);
	//decode_assembly(arr[5], arr[4], 1, filename);
	
	
	for (count_up = 0; count_up < i; count_up++) {

		printf("Counter %d: %02x %d\n", count_up, arr[count_up], arr[count_up]);

		if ((count_up % 2) == 0 && (count_up != i - 1)) {
			printf("count up mod: %d\n", count_up);
	//		printf("This is low: %d and high:%d\n", count_up, count_up_h);
			printf("%04x \n", address_arr[count_up]);
			//printf("This is the filename: %s \n", filename);
			decode_assembly(arr[count_up +1], arr[count_up], address_arr[count_up]);
		}
		count_up++;
		//count_up_h++;
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