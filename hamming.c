//
// Created by Kevin Dixson on 2019-10-04.
//

#include "hamming.h"
#define BIT_WIDTH 4
#define G_ROWS 7
#define G_COLS BIT_WIDTH
#define H_ROWS 3
#define H_COLS G_ROWS

int** generate(int** A, int rows, int cols);
int* getSyndrome(int* A);
int** getHammingArray(unsigned short data);
void toBinary(unsigned int data, int width, int* dataArray);
int toDecimal(int width, int* num);
int decodeHammingUnsafe(unsigned short data);

unsigned int correctMalformed(unsigned int data) {
   unsigned int wrongBitMask = (unsigned int) pow(2, G_ROWS - isMalformed(data));
   return data ^ wrongBitMask;
}

// 1 is 0th bit, 2 is 1st bit, etc...
// 0 is no error
unsigned int isMalformed(int data) {
   int hamming[G_ROWS] = {0};
   int* syndrome;

   toBinary(data, G_ROWS, hamming);

   syndrome = getSyndrome(hamming);

   return toDecimal(H_ROWS, syndrome);
}

// Little endian
void toBinary(unsigned int data, int width, int* dataArray) {
   for (unsigned int i = 0; i < width; i++) {
      int res =  (unsigned int) (data & (unsigned short) pow(2, i)) >> i;
      dataArray[width - i - 1] = res; // load MSB as 0th index
   }
}

int** getHammingArray(unsigned short data) {
   int dataArray[BIT_WIDTH] = {0};

   toBinary(data, BIT_WIDTH, dataArray);

   int** D = transposeToVertical((int*) dataArray, BIT_WIDTH);
   int** hamming = generate(D, BIT_WIDTH, 1);

   free(D);

   for (int i = 0; i < G_ROWS; i++) {
      hamming[i][0] %= 2;
   }

   return hamming;
}

int encodeHamming(unsigned short data) {
   int** hamming = getHammingArray(data);
   return toDecimal(G_ROWS, transposeToHorizontal(hamming, G_ROWS));
}

int decodeHammingUnsafe(unsigned short data) {
   unsigned short bigVal = data & 23u;
   unsigned short msb = 8u & (bigVal >> 1u);

   return  (bigVal | msb) & 15u;
}

int safeDecodeHamming(unsigned short data) {
   return decodeHammingUnsafe(
         isMalformed(data) ?
         correctMalformed(data) :
         data
   );
}

int toDecimal(int width, int* num) {
   int decimalVal = 0;

   for (int i = 0; i < width; i++) {
      unsigned int power = (unsigned int) pow(2, width - i - 1);
      decimalVal += num[i] ? power : 0;
   }

   return decimalVal;
}

// multiply GA.
// result is array with result bits MSB is 0th index
int** generate(int** A, int rows, int cols) {
   int** result = calloc(sizeof(char*), G_ROWS);
   int** G = malloc(sizeof(int*) * G_ROWS);

   // carefully selected from https://en.wikipedia.org/wiki/Hamming(7,4)
   int Ga[G_COLS] = {1, 1, 0, 1};
   int Gb[G_COLS] = {1, 0, 1, 1};
   int Gc[G_COLS] = {1, 0, 0, 0};
   int Gd[G_COLS] = {0, 1, 1, 1};
   int Ge[G_COLS] = {0, 1, 0, 0};
   int Gf[G_COLS] = {0, 0, 1, 0};
   int Gg[G_COLS] = {0, 0, 0, 1};
   G[0] = &Ga[0];
   G[1] = &Gb[0];
   G[2] = &Gc[0];
   G[3] = &Gd[0];
   G[4] = &Ge[0];
   G[5] = &Gf[0];
   G[6] = &Gg[0];

   for (int i = 0; i < G_ROWS; i++) {
      int* temp = calloc(sizeof(int), G_COLS);
      result[i] = temp;
   }

   multiply(G, G_COLS, G_ROWS, A, cols, rows, result);

   return result;
}

// multiply HA.
// result is array with result bits MSB is 0th index
int* getSyndrome(int* A) {
   int** parity_matrix = malloc(sizeof(int*) * H_ROWS);
   int** result = malloc(sizeof(int*) * H_ROWS);

   // carefully selected from https://en.wikipedia.org/wiki/Parity-check_matrix
   int Ha[H_COLS] = {1, 0, 1, 0, 1, 0, 1};
   int Hb[H_COLS] = {0, 1, 1, 0, 0, 1, 1};
   int Hc[H_COLS] = {0, 0, 0, 1, 1, 1, 1};
   parity_matrix[0] = &Ha[0];
   parity_matrix[1] = &Hb[0];
   parity_matrix[2] = &Hc[0];

   for (int i = 0; i < H_ROWS; i++) {
      int* temp = calloc(sizeof(int), G_COLS);
      result[i] = temp;
   }

   multiply(parity_matrix, H_COLS, H_ROWS,
         transposeToVertical(A, G_ROWS), 1, G_ROWS, result);

   for (int i = 0; i < H_ROWS; i++) {
      result[i][0] %= 2;
   }

   return transposeToHorizontal(result, H_ROWS);
}