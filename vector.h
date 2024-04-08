#ifndef VECTOR_H_
#define VECTOR_H_

#include "matrix.h"

/*
 * data types
 */

typedef struct Vector {
    float* values;
    int rows;
} Vector;

/*
 * functions
 */

Vector vect_init_bare(int rows);
Vector vect_init_data(int rows, float* data);
int vect_add(Vector* vin1, Vector* vin2, Vector* vout);
int vect_sub(Vector* vin1, Vector* vin2, Vector* vout);
int vect_vect_prod(Vector* vin1, Vector* vin2, float* out);
int vect_matx_prod(Matrix* min, Vector* vin, Vector* vout);
void vect_print(Vector* v);

#endif
