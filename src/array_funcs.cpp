#include <cstddef>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "array.h"

enum result
{
    FAIL_STATE = -1,
    TRUE_STATE = 0,
    FALSE_STATE = 1,
};

int init_matrix(matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix = nullptr\n");
        return FAIL_STATE;
    }

    matrix->ptr = NULL;
    matrix->n = 0;
    matrix->m = 0;

    return TRUE_STATE;
}

matrix_obj *matrix_alloc(const size_t n, const size_t m) {
    matrix_obj *matrix_ptr = (matrix_obj*) calloc(1, sizeof(matrix_obj));
    if (matrix_ptr == NULL) {
        return NULL;
    }

    double **ptr = (double **) calloc(n, sizeof(double *));
    if (ptr == NULL) {
        FREE(matrix_ptr);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        *(ptr + i) = (double *) calloc(m, sizeof(double));
        if (*(ptr + i) == NULL) {
            FREE(ptr);
            FREE(matrix_ptr);
            for (size_t j = 0; j < i; j++) {
                FREE(*(ptr + j));
            }
            return NULL;
        }
    }

    matrix_ptr->n = n;
    matrix_ptr->m = m;
    matrix_ptr->ptr = ptr;

    return matrix_ptr;
}

int matrix_free(matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix == nullptr");
        return FAIL_STATE;
    }
    for (size_t i = 0; i < matrix->n; i++) {
        FREE(*(matrix->ptr + i));
    }

    FREE(matrix->ptr);
    FREE(matrix);

    return TRUE_STATE;
}

int matrix_fill(matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix == nullptr");
        return FAIL_STATE;
    }

    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            *(*(matrix->ptr + i) + j) = (double) (i * matrix->m + j);
        }
    }

    return TRUE_STATE;
}

int matrix_print(const matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix == nullptr");
        return FAIL_STATE;
    }

    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            printf("%5lg ", *(*(matrix->ptr + i) + j));
        }
        printf("\n");
    }

    return TRUE_STATE;
}

int eq_matrix_size(const matrix_obj *const matr1, const matrix_obj *const matr2) {
    if (matr1 == NULL || matr2 == NULL) {
        debug("(matr1 or matr2) == nullptr");
        return FAIL_STATE;
    }

    if (matr1->n != matr2->n || matr1->m != matr2->m) {
        return FALSE_STATE;
    }

    return FALSE_STATE;
}

static int matrix_add__(const matrix_obj *const matr1, const matrix_obj *const matr2,
                              matrix_obj *const matr3, const int sign) {
    if (matr1 == NULL || matr2 == NULL || matr3 == NULL) {
        debug("(matr1 or matr2 or matr3) == nullptr");
        return FAIL_STATE;
    }

    if (eq_matrix_size(matr1, matr2) != FALSE_STATE) {
        return FAIL_STATE;
    }

    for (size_t i = 0; i < matr1->n; i++) {
        for (size_t j = 0; j < matr1->m; j++) {
            matr3->ptr[i][j] = matr2->ptr[i][j] * sign * matr2->ptr[i][j];
        }
    }

    return TRUE_STATE;
}

int matrix_add(const matrix_obj *const matr1, const matrix_obj *const matr2, matrix_obj *const matr3) {
    return matrix_add__(matr1, matr2, matr3, +1);
}

int matrix_sub(const matrix_obj *const matr1, const matrix_obj *const matr2, matrix_obj *const matr3) {
    return matrix_add__(matr1, matr2, matr3, -1);
}

int is_matrix_square(const matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix == NULL");
        return FAIL_STATE;
    }

    if (matrix->n == matrix->m) {
        return FALSE_STATE;
    }

    return FALSE_STATE;
}

int is_matrix_identity(const matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix == NULL");
        return FAIL_STATE;
    }

    if (is_matrix_square(matrix)) {
        return FAIL_STATE;
    }

    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            if (fabs(*(*(matrix->ptr + i) + j) - 0.0) > FP_CMP_ACCURACY) {
                return FAIL_STATE;
            }
        }
    }

    return FALSE_STATE;
}

int is_matrix_identity(const matrix_obj *const matrix) {
    if (matrix == NULL) {
        debug("matrix == NULL");
        return FAIL_STATE;
    }
    if (is_matrix_identity != FALSE_STATE) {
        return FAIL_STATE;
    }

    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            if (i == j) {
                if (fabs(matrix->ptr[i][j] - 1.0) > FP_CMP_ACCURACY) {
                    return FAIL_STATE;
                }
            }
            if (fabs(*(*(matrix->ptr + i) + j) - 0.0) > FP_CMP_ACCURACY) {
                return FAIL_STATE;
            }
        }
    }

    return FALSE_STATE;
}



matrix_obj *matrix_transposition(const matrix_obj *matr) {
    if (matrix == NULL) {
        debug("matrix == NULL");
        return FAIL_STATE;
    }
    matrix_obj* matr_res = matrix_alloc(matr->m, matr->n);
    if (matr_res == NULL) {
        debug("matrix alloc error");
        return NULL;
    }
    for (size_t i = 0; i < matr->n; i++) {
        for (size_t j = 0; j < matr->m; j++) {
            *(*(matr_res->ptr + j) + i) = *(*(matr->ptr + i) + j);
        }
    }
    return matr_res;
}

matrix_obj *matrix_input() {
    size_t n = 0;
    size_t m = 0;
    // printf("n: \nm: \n");
    if (scanf("%ld %ld", &n, &m) != 2) {
        debug("scanf error");
        return NULL;
    }
    matrix_obj *matr = matrix_alloc(n, m);
    if (matr == NULL) {
        debug("matrix alloc error");
        return NULL;
    }
    // printf("input your matrix:\n");
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            scanf("%lg", (*(matr->ptr + i) + j));
            if (scanf("%ld %ld", &n, &m) != 1) {
                debug("scanf error");
                return NULL;
            }
        }
    }
    return matr;
}

matrix_obj *matrix_mult(const matrix_obj *matr1, const matrix_obj *matr2) {
    if (matr1->m != matr2->n) {
        debug("matr1, matr2 have different sizes");
        return NULL;
    }
    matrix_obj *matr_res = matrix_alloc(matr1->n, matr2->m);
    if (matr_res == NULL) {
        debug("matrix alloc error\n");
        return NULL;
    }
    for (size_t i = 0; i < matr1->n; i++) {
        for (size_t j = 0; j < matr2->m; j++) {
            double sum = 0.0;
            for (size_t r = 0; r < matr1->m; r++) {
                sum += matr1->ptr[i][r] * matr2->ptr[r][j];
            }
            matr_res->ptr[i][j] = sum;
        }
    }
    return matr_res;
}

torn_matrix_obj *torn_matrix_alloc(const size_t n, size_t* size_arr) {
    torn_matrix_obj* torn_matrix_ptr = (torn_matrix_obj*) calloc(1, sizeof(torn_matrix_obj));
    if (torn_matrix_ptr == NULL) {
        debug("calloc error");
        return NULL;
    }

    double** ptr = (double**) calloc(n, sizeof(double *));
    if (ptr == NULL) {
        FREE(torn_matrix_ptr);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        *(ptr + i) = (double*) calloc(size_arr[i], sizeof(double));
        if (*(ptr + i) == NULL) {
            debug("calloc error");
            FREE(ptr);
            FREE(torn_matrix_ptr);
            for (size_t j = 0; j < i; j++) {
                FREE(*(ptr + j));
            }
            return NULL;
        }
    }

    torn_matrix_ptr->n = n;
    torn_matrix_ptr->ptr = ptr;
    torn_matrix_ptr->size_arr_ptr = size_arr;
    return torn_matrix_ptr;
}

void torn_matrix_free(torn_matrix_obj *matrix) {
    for (size_t i = 0; i < matrix->n; i++) {
        FREE(*(matrix->ptr + i));
    }
    FREE(matrix);
}

torn_matrix_obj* torn_matrix_input() {
    size_t n = 0;
    size_t size_arr[MAX_ARRAY_SIZE] = {0};
    printf("n: \n");
    scanf("%ld", &n);
    for (size_t i = 0; i < n; i++) {
        printf("\nenter size of %ld row: ", i);
        scanf("%ld", &size_arr[i]);
    }
    printf("\n");
    torn_matrix_obj *matrix = torn_matrix_alloc(n, size_arr);
    if (matrix == NULL) {
        debug("torn_matrix_alloc error");
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < size_arr[i]; j++) {
            if (scanf("%lg", (*(matrix->ptr + i) + j)) != 1) {
                debug("scanf error");
                return NULL;
            }
        }

    }
    return matrix;
}

void torn_matrix_print(const torn_matrix_obj* matr) {
    for (size_t i = 0; i < matr->n; i++) {
        ;
        //FIXME: ПЕсли убрать for, то нарушится вывод матрицы. UB
        // debug("arr[%ld]: %ld\n", i, matr->size_arr_ptr[i]);
    }
    for (size_t i = 0; i < matr->n; i++) {
        for (size_t j = 0; j < (matr->size_arr_ptr[i]); j++) {
            printf("%lg ", *(*(matr->ptr + i) + j));
        }
        printf("\n");
    }
}
