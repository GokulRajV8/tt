#ifndef VECTOR_H_
#define VECTOR_H_

#include "common.h"

/*
 * data types
 */

struct Vector {
    float* values;
    uint32_t rows;
};

/*
 * functions
 */

struct Vector vect_init_bare(uint32_t rows);
struct Vector vect_init_data(uint32_t rows, float* data);
void vect_delete(struct Vector* v);

inline float* vect_get(struct Vector* v, uint32_t rid);
void vect_resize(struct Vector* v, uint32_t rows);
void vect_copy(struct Vector* vsrc, struct Vector* vdest);
void vect_print(struct Vector* v, char* name);

int vect_add(struct Vector* vin1, struct Vector* vin2, struct Vector* vout);
int vect_sub(struct Vector* vin1, struct Vector* vin2, struct Vector* vout);
int vect_vect_prod(struct Vector* vin1, struct Vector* vin2, float* out);

#endif
