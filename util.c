//
// Created by Kevin Dixson on 2019-10-07.
//

#include "util.h"

unsigned int oddOnes(unsigned int input) {
   unsigned int count = 0;

   while (input) {
      count += input & 1u;
      input >>= 1u;
   }

   return count % 2;
}
