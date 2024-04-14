#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>

#include "vector.h"

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

inline float* matx_get(Matrix* m, int rid, int cid);
void matx_print(Matrix* m, char* name);

int matx_add(Matrix* min1, Matrix* min2, Matrix* mout);
int matx_sub(Matrix* min1, Matrix* min2, Matrix* mout);
int matx_vect_prod(Matrix* min, Vector* vin, Vector* vout);
int matx_matx_prod(Matrix* min1, Matrix* min2, Matrix* mout);

#endif
