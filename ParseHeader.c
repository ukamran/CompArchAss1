/*
* This file and its contents have been used as is from the template provided by Dr Larry Highes.
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
	unsigned int byte;
	unsigned int chksum;
	unsigned int pos;
	unsigned int i;

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
			printf("%c", byte);
			chksum += CHAR_MASK(byte);
			pos += 2;
		}
		break;
	case '1': /* Data (Instruction or data) record */
		/* Print first address and bytes */
		printf("Address: %04x: ", address);
		for (i = 0; i <= length; i++)
		{
			sscanf_s(&srec[pos], "%2x", &byte);
#ifdef DISPLAY_BYTE
			printf("%02x ", byte);
#endif
			chksum += CHAR_MASK(byte);
			pos += 2;
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