#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdint.h>
#include <stdio.h>

#include "vector.h"

/*
 * data types
 */

typedef struct {
    float* values;
    uint32_t rows;
    uint32_t columns;
} Matrix;

/*
 * functions
 */

Matrix matx_init_bare(uint32_t rows, uint32_t columns);
Matrix matx_init_data(uint32_t rows, uint32_t columns, float* data);
void matx_delete(Matrix* m);

inline float* matx_get(Matrix* m, uint32_t rid, uint32_t cid);
void matx_print(Matrix* m, char* name);

int matx_add(Matrix* min1, Matrix* min2, Matrix* mout);
int matx_sub(Matrix* min1, Matrix* min2, Matrix* mout);
int matx_vect_prod(Matrix* min, Vector* vin, Vector* vout);
int matx_matx_prod(Matrix* min1, Matrix* min2, Matrix* mout);

#endif
