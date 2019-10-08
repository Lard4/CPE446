#include "parity.h"

// when the LSB is 1 and there are odd num of set bits
int isMalformedParity(unsigned int input) {
   return (input & 1u) && (oddOnes(input));
}

unsigned int decodeParity(unsigned int input) {
   return input >> 1u;
}

// add a 1 to the right side if there is an odd number of set bits.
unsigned int encodeParity(unsigned int input) {
   unsigned int k = input << 1u;
   return k | oddOnes(input);
}