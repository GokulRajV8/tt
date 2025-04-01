// Contains all the functions used internally by TT library

#ifndef TT_IFUNCTIONS_H
#define TT_IFUNCTIONS_H

#include "data.h"
#include "idata.h"

// Vector

struct TTVector* vector_list_init(unsigned int count, unsigned int* sizes);

void vector_list_delete(unsigned int count, struct TTVector* vlist);

void vector_resize(struct TTVector* v, unsigned int rows);

void vector_add(struct TTVector* vin1, struct TTVector* vin2,
                struct TTVector* vout);

void vector_print(struct TTVector* v, char* name);

// Matrix

struct TTMatrix matrix_init(unsigned int rows, unsigned int cols);
void matrix_delete(struct TTMatrix* m);

float* matrix_get_data(struct TTMatrix* m, unsigned int rid, unsigned int cid);

void matrix_vector_prod(struct TTMatrix* min, struct TTVector* vin,
                        struct TTVector* vout);

void matrix_print(struct TTMatrix* m, char* name);

// Layer

void layer_transform(struct TTLayer* l, struct TTVector* vin,
                     struct TTVector* vout);

// Block

struct GranularLayerInput block_transform_granular(struct TTBlock* b,
                                                   struct TTVector* vin,
                                                   struct TTVector* vout);

#endif
