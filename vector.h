#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdint.h>
#include <stdio.h>

/*
 * data types
 */

typedef struct {
    float* values;
    uint32_t rows;
} Vector;

/*
 * functions
 */

Vector vect_init_bare(uint32_t rows);
Vector vect_init_data(uint32_t rows, float* data);
void vect_delete(Vector* v);

inline float* vect_get(Vector* v, uint32_t rid);
void vect_resize(Vector* v, uint32_t rows);
void vect_copy(Vector* vsrc, Vector* vdest);
void vect_print(Vector* v, char* name);

int vect_add(Vector* vin1, Vector* vin2, Vector* vout);
int vect_sub(Vector* vin1, Vector* vin2, Vector* vout);
int vect_vect_prod(Vector* vin1, Vector* vin2, float* out);

#endif
