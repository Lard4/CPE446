#ifndef CPE446LAB2_PARITY_H
#define CPE446LAB2_PARITY_H

#include "main.h"
#include "util.h"

unsigned int encodeParity(unsigned int input);
unsigned int decodeParity(unsigned int input);
int isMalformedParity(unsigned int input);

#endif //CPE446LAB2_PARITY_H
