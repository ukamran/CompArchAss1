/*
 - Bit extraction using bit masks and shifts
 - Masks are ANDing with a bit pattern to extract a specific set of bits
 - 
 - Shifts (in this case), are right shifts to the LSBit
 - Shift and mask or mask and shift - your choice
 - Patterns to extract:
     15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
   | A | A | B | B . B | B | C | C . C | C | C | D . E | E | E | E |
 - ECED 3403
 - 22 May 21
*/

/* Shift, then extract (mask): */
#define A(x)    (((x) >> 14) & 0x03)
#define B(x)    (((x) >> 10) & 0x0F)
/* Or, extract (mask) and then shift: */
#define C(x)    (((x) & 0x3E0) >> 5)
#define D(x)    (((x) & 0x10) >> 4)
/* With LSBits, mask only*/
#define E(x)    ((x) & 0x0F)

void mask_bits(int bits[], int value)
{
/*
 - Extract the bits in value using the defined masks
 - bits[] is the base address of an integer array 
*/
bits[0] = A(value);
bits[1] = B(value);
bits[2] = C(value);
bits[3] = D(value);
bits[4] = E(value);
}