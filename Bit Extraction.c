/*
 - Bit Extraction
 - Two methods of extracting bits
 - In this example, we want to extract the following 5 groups of bits:
     15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
   | A | A | B | B . B | B | C | C . C | C | C | D . E | E | E | E |
 - Notes:
   - Nibbles are anthropogenic groupings, the machine ignores them
   - 
 - ECED 3403
 - 22 May 21
*/
#include <stdio.h>
#include "Bit Extraction.h"

void print_bitcount(int count[])
{
/* Display the value of each bit grouping */
printf("A: %d. B: %d. C: %d. D: %d E: %d\n", 
    count[0], count[1], count[2], count[3], count[4]);
}

main()
{
/*
 - Mainline to demonstrate C function calls passing arrays
 - Calls three functions for illustrate different approaches to 
   bit-extraction
*/
unsigned bit_count[TOTAL_BITS];

/* AND and shift: */
printf("AND and shift:\n");
mask_bits(bit_count, 0xFFFF);
print_bitcount(bit_count);
mask_bits(bit_count, 0);
print_bitcount(bit_count);
mask_bits(bit_count, 0xF0F0);
print_bitcount(bit_count);

/* Struct and union */
printf("Struct and union:\n");
struct_bits_1(bit_count, 0xFFFF);
print_bitcount(bit_count);
struct_bits_1(bit_count, 0);
print_bitcount(bit_count);
struct_bits_1(bit_count, 0xF0F0);
print_bitcount(bit_count);

/* Struct pointer*/
printf("Struct pointer:\n");
struct_bits_2(bit_count, 0xFFFF);
print_bitcount(bit_count);
struct_bits_2(bit_count, 0);
print_bitcount(bit_count);
struct_bits_2(bit_count, 0xF0F0);
print_bitcount(bit_count);

getchar();

}