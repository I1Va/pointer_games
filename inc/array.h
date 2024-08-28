#include <cstddef>
#include <string.h>

#include "colors.h"

#ifndef ARRAY_H
#define ARRAY_H

#define FREE(ptr)           \
    do {                    \
        free(ptr); ptr = NULL; \
    } while(0)

// #define FREE(ptr)                \
//     ({                           \
//         typeof(ptr) ptr__ = ptr; \
//         free(ptr);               \
//         ptr = NULL;              \
//         ptr__                    \
//     })

#ifdef _DEBUG
#define debug(str_, ...) fprintf_red(stderr, "[%s: %d] " str_, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define debug(str_, ...)
#endif // _DEBUG

const double FP_CMP_ACCURACY = 1e-4;

const size_t MAX_ARRAY_SIZE = 256;

struct matrix_obj {
    double** ptr;
    size_t n;
    size_t m;
};

struct torn_matrix_obj {
    double **ptr;
    size_t *size_arr_ptr;
    size_t n;
};

void init_matrix(matrix_obj *matrix);

matrix_obj *matrix_alloc(const size_t n, const size_t m);

void matrix_free(matrix_obj *matrix);

void matrix_fill(matrix_obj* matrix);

void matrix_print(const matrix_obj *matrix);

bool eq_matrix_size(const matrix_obj* matr1, const matrix_obj* matr2);

int matrix_add(const matrix_obj *matr1, const matrix_obj *matr2, matrix_obj *matr3);

bool check_matrix_identity(const matrix_obj *matr);

bool check_matrix_diagonality(const matrix_obj *matr);

matrix_obj* matrix_transposition(const matrix_obj *matr);

matrix_obj* matrix_input();

matrix_obj *matrix_mult(const matrix_obj *matr1, const matrix_obj *matr2);

torn_matrix_obj *torn_matrix_alloc(const size_t n, size_t size_arr[]);

void torn_matrix_free(torn_matrix_obj *matrix);

torn_matrix_obj* torn_matrix_input();

void torn_matrix_print(const torn_matrix_obj* matr);

#endif // ARRAY_H