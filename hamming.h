//
// Created by Kevin Dixson on 2019-10-04.
//

#ifndef CPE446LAB2_HAMMING_H
#define CPE446LAB2_HAMMING_H

#include "main.h"
#include "matrix.h"

int encodeHamming(unsigned short data);
int decodeHamming(unsigned short data);
unsigned int isMalformed(int data);
unsigned int correctMalformed(unsigned int data);

#endif //CPE446LAB2_HAMMING_H
