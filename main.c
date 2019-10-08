#include "main.h"

void matrices();

int main() {
   //matrices();

   printf("101101 aka 45 with parity then removed: %d\n", decodeParity(encodeParity(45u)));
   printf("101101 aka 45 with parity (90): %d\n\n", encodeParity(45u));

   printf("111 aka 7 with parity (15): %d\n", encodeParity(7u));
   printf("111 aka 7 with parity then removed: %d\n\n", decodeParity(encodeParity(7u)));

   printf("should not be malformed (0): %d\n", isMalformedParity(45u));
   printf("should be malformed (1): %d\n\n", isMalformedParity(7u));

   printf("H(1011) should be 51: %d\n", encodeHamming(11));
   printf("H(1111) should be 127: %d\n", encodeHamming(15));
   printf("H(0000) should be 0: %d\n", encodeHamming(0));
   printf("H(1000) should be 112: %d\n", encodeHamming(8));
   printf("H(1001) should be 25: %d\n\n", encodeHamming(9));

   printf("isWellFormed 51 should be 0: %d\n", isMalformed(51));
   printf("isWellFormed 127 should be 0: %d\n", isMalformed(127));
   printf("isWellFormed 0 should be 0: %d\n", isMalformed(0));
   printf("isWellFormed 112 should be 0: %d\n", isMalformed(112));
   printf("isWellFormed 25 should be 0: %d\n\n", isMalformed(25));

   printf("isWellFormed 1 should be !0: %d\n", isMalformed(1));
   printf("isWellFormed 3 should be !0: %d\n", isMalformed(3));
   printf("isWellFormed 55 should be 5: %d\n\n", isMalformed(55));

   printf("55 corrected should be 51: %d\n", correctMalformed(55));
   return 0;
}

void matrices() {
   printf("==============\n===MATRICES===\n==============\n");
   printf("0, 1, 1\n1, 0, 2\n1, 2, 1\n");
   printf("*******\n");
   printf("1, 2, 3\n0, 1, 2\n2, 2, 2\n");

   int** A = malloc(sizeof(int*) * 3);
   int Aa[3] = {0, 1, 1};
   int Ab[3] = {1, 0, 2};
   int Ac[3] = {1, 2, 1};
   A[0] = &Aa[0];
   A[1] = &Ab[0];
   A[2] = &Ac[0];

   int** B = malloc(sizeof(int*) * 3);
   int Ba[3] = {1, 2, 3};
   int Bb[3] = {0, 1, 2};
   int Bc[3] = {2, 2, 2};
   B[0] = &Ba[0];
   B[1] = &Bb[0];
   B[2] = &Bc[0];

   int** result = malloc(sizeof(int*) * 3);
   int Ra[3] = {0};
   int Rb[3] = {0};
   int Rc[3] = {0};
   result[0] = &Ra[0];
   result[1] = &Rb[0];
   result[2] = &Rc[0];

   multiply(A, 3, 3, B, 3, 3, result);

   printf("=======\n");
   printf("actual result:\n");
   display(result, 3, 3);
   printf("expected result:\n");
   printf("2, 3, 4\n5, 6, 7\n3, 6, 9\n");

   printf("\n\n\n");

   free(A);
   free(B);
   free(result);

   printf("1,\t2,\t10,\t10\n11,\t22,\t23,\t12\n9,\t2,\t0,\t4\n");
   printf("*******\n");
   printf("11\n0\n44\n3\n");

   A = malloc(sizeof(int*) * 4);
   int Ax[4] = {1, 2, 10, 10};
   int Ay[4] = {11, 22, 23, 12};
   int Az[4] = {9, 2, 0, 4};
   A[0] = &Ax[0];
   A[1] = &Ay[0];
   A[2] = &Az[0];

   B = malloc(sizeof(int*) * 4);
   int Bx[1] = {11};
   int By[1] = {0};
   int Bz[1] = {44};
   int Bq[1] = {3};
   B[0] = &Bx[0];
   B[1] = &By[0];
   B[2] = &Bz[0];
   B[3] = &Bq[0];

   result = malloc(sizeof(int*) * 4);
   int Rx[3] = {0};
   int Ry[3] = {0};
   int Rz[3] = {0};
   int Rq[3] = {0};
   result[0] = &Rx[0];
   result[1] = &Ry[0];
   result[2] = &Rz[0];
   result[3] = &Rq[0];

   if (-1 == multiply(A, 4, 3, B, 1, 4, result)) {
      printf("FAILURE");
      exit(1);
   }

   printf("=======\n");
   printf("actual result:\n");
   display(result, 3, 1);

   printf("expected result:\n");
   printf("481\n1169\n111");

   free(A);
   free(result);

   printf("\n\n\n");

   printf("transpose horizontal:\n");
   int* p = transposeToHorizontal(B, 4);
   for (int i = 0; i < 4; i++) {
      printf("%d, ", p[i]);
   }
   printf("\n");

   printf("transpose vertical:\n");
   int** q = transposeToVertical(p, 4);
   for (int i = 0; i < 4; i++) {
      printf("%d\n", (*(q+i))[0]);
   }
   printf("\n");
}