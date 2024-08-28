
#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"

/* 
pading
    Packing, on the other hand prevents compiler from doing padding - this has to be explicitly requested - under
    GCC it's __attribute__((__packed__)), so the following:

    struct __attribute__((__packed__)) mystruct_A {
        char a;
        int b;
        char c;
    };
*/

// pragma

int main() {
    torn_matrix_obj *matrix_ptr = torn_matrix_input();
    torn_matrix_print(matrix_ptr);
    
    
}