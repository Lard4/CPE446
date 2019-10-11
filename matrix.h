//
// Created by Kevin Dixson on 2019-10-07.
//

#ifndef CPE446LAB2_MATRIX_H
#define CPE446LAB2_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

int multiply(int* A[], int A_cols, int A_rows,
             int* B[], int B_cols, int B_rows,
             int* result[]);
int** multiplyABFT(int* A[], int A_cols, int A_rows,
             int* B[], int B_cols, int B_rows,
             int* result[]);
int** transposeToVertical(int* M, int length);
int* transposeToHorizontal(int** M, int length);
void display(int** M, int rows, int cols);
int sumColumn(int **M, int height, int colNum);
int** addFullSums(int** M, int rows, int cols);
int** addColumnSums(int** M, int rows, int cols);
int** addRowSums(int** M, int rows, int cols);

#endif //CPE446LAB2_MATRIX_H
