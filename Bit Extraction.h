#pragma once
/*
 - Bit extraction code header file
 - List entry points (for mainline's calls the the functions
 - ECED 3403
 - 22 May 21
*/

#define TOTAL_BITS	5

/* External entry points */
extern void mask_bits(int bits[], int value);
extern void struct_bits_1(int bits[], int value);
extern void struct_bits_2(int bits[], int value);
