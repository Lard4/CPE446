//
// Created by Kevin Dixson on 2019-10-07.
//

#include "matrix.h"

void getCol(int* A[], int A_rows, int colNumber, int result[]);
int dotProduct(const int A[], const int B[], int length);

int dotProduct(const int A[], const int B[], int length) {
   int result = 0;

   for (int i = 0; i < length; i++) {
      result += A[i] * B[i];
   }

   return result;
}

// result must be of length M_rows
// colNumber is 0-based index of desired column
void getCol(int** M, int M_rows, int colNumber, int result[]) {
   for (int i = 0; i < M_rows; i++) {
      result[i] = M[i][colNumber];
   }
}

// compute AB
// A, B, and result should be dynamically allocated
int multiply(int* A[], int A_cols, int A_rows,
             int* B[], int B_cols, int B_rows,
             int* result[]) {
   if (A_cols != B_rows)
      return -1;

   for (int i = 0; i < A_rows; i++) {
      int* a_row = *(A+i);

      for (int j = 0; j < B_cols; j++) {
         int* b_col = calloc(sizeof(int), B_rows);
         getCol(B, B_rows, j, b_col);

         result[i][j] = dotProduct(a_row, b_col, A_cols);
         free(b_col);
      }
   }

   return 0;
}

// compute AB with checksums
int** multiplyABFT(int* A[], int A_cols, int A_rows,
                 int* B[], int B_cols, int B_rows,
                 int* result[]) {
   A = addFullSums(A, A_rows, A_cols);
   B = addFullSums(B, B_rows, B_cols);
   result = addFullSums(result, A_rows, B_cols);

   multiply(A, A_cols, A_rows,
            B, B_cols, B_rows,
            result);

   return result;
}

int** transposeToVertical(int* M, int length) {
   int** vertical = malloc(sizeof(int*) * length);

   for (int i = 0; i < length; i++) {
      vertical[i] = malloc(sizeof(int));
      *(vertical[i]) =  M[i];
   }

   return vertical;
}

int* transposeToHorizontal(int** M, int length) {
   int* horizontal = malloc(sizeof(int) * length);

   for (int i = 0; i < length; i++) {
      horizontal[i] = (*(M + i))[0];
   }

   return horizontal;
}

void display(int** M, int rows, int cols) {
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
         printf("%d%s", M[i][j], j == cols-1 ? "\n" : ", ");
      }
   }
}

int sumColumn(int **M, int rows, int colNum) {
   int result = 0;

   for (int i = 0; i < rows; i++) {
      result += M[i][colNum];
   }

   return result;
}

int** addFullSums(int** M, int rows, int cols) {
   // add memory for column-sum row
   M = realloc(M, sizeof(int*) * (rows + 1));

   for (int i = 0; i < rows; i++) {
      int rowSum = 0;
      int newSize = (cols + 1) * sizeof(M[0]);

      // add row-sum column
      M[i] = realloc(M[i], newSize);

      for (int j = 0; j < cols; j++) {
         rowSum += M[i][j];
      }

      // add row sum to end this row
      M[i][cols] = rowSum;
   }


   M[rows] = malloc(sizeof(int) * (cols + 1));

   // for every COLUMN, add its sum to the bottom row @ index of current column.
   // cols + 1 because we added a column that needs a sum
   for (int i = 0; i < cols + 1; i++) {
      M[rows][i] = sumColumn(M, rows, i);
   }

   return M;
}

int** addRowSums(int** M, int rows, int cols) {
   for (int i = 0; i < rows; i++) {
      int rowSum = 0;
      int newSize = (cols + 1) * sizeof(M[0]);

      // add row-sum column
      M[i] = realloc(M[i], newSize);

      for (int j = 0; j < cols; j++) {
         rowSum += M[i][j];
      }

      // add row sum to end this row
      M[i][cols] = rowSum;
   }

   return M;
}

int** addColumnSums(int** M, int rows, int cols) {
   // add memory for column-sum row
   M = realloc(M, sizeof(int*) * (rows + 1));

   // memory for new bottom row
   M[rows] = malloc(sizeof(int) * (cols + 1));

   // for every COLUMN, add its sum to the bottom row @ index of current column.
   // cols + 1 because we added a column that needs a sum
   for (int i = 0; i < cols + 1; i++) {
      M[rows][i] = sumColumn(M, rows, i);
   }

   return M;
}