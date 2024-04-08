#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>

/*
 * data types
 */

typedef struct Matrix {
    float* values;
    int rows;
    int columns;
} Matrix;

/*
 * functions
 */

Matrix matx_init_bare(int rows, int columns);
Matrix matx_init_data(int rows, int columns, float* data);
int matx_add(Matrix* min1, Matrix* min2, Matrix* mout);
int matx_sub(Matrix* min1, Matrix* min2, Matrix* mout);
int matx_prod(Matrix* min1, Matrix* min2, Matrix* mout);
void matx_print(Matrix* m);

#endif
