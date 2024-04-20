#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdint.h>
#include <stdio.h>

#include "vector.h"

/*
 * data types
 */

struct Matrix {
    float* values;
    uint32_t rows;
    uint32_t columns;
};

/*
 * functions
 */

struct Matrix matx_init_bare(uint32_t rows, uint32_t columns);
struct Matrix matx_init_data(uint32_t rows, uint32_t columns, float* data);
void matx_delete(struct Matrix* m);

inline float* matx_get(struct Matrix* m, uint32_t rid, uint32_t cid);
void matx_resize(struct Matrix* m, uint32_t rows, uint32_t columns);
void matx_copy(struct Matrix* msrc, struct Matrix* mdest);
void matx_print(struct Matrix* m, char* name);

int matx_add(struct Matrix* min1, struct Matrix* min2, struct Matrix* mout);
int matx_sub(struct Matrix* min1, struct Matrix* min2, struct Matrix* mout);
int matx_vect_prod(struct Matrix* min, struct Vector* vin, struct Vector* vout);
int matx_matx_prod(struct Matrix* min1, struct Matrix* min2,
                   struct Matrix* mout);

#endif
