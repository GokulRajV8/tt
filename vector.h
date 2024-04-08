#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>

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
void vect_print(Vector* v);

#endif
