// Contains all the functions used internally by TT library

#ifndef TT_IFUNCTIONS_H
#define TT_IFUNCTIONS_H

#include "data.h"

// Vector

void vector_resize(struct TTVector* v, unsigned int rows);

void vector_add(struct TTVector* vin1, struct TTVector* vin2,
                struct TTVector* vout);

// Matrix

struct TTMatrix matrix_init(unsigned int rows, unsigned int cols);
void matrix_delete(struct TTMatrix* m);

float* matrix_get_data(struct TTMatrix* m, unsigned int rid, unsigned int cid);

void matrix_vector_prod(struct TTMatrix* min, struct TTVector* vin,
                        struct TTVector* vout);

// Layer

void layer_transform(struct TTLayer* l, struct TTVector* vin,
                     struct TTVector* vout);

#endif
