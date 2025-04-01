// Contains all the functions exposed by TT library

#ifndef TT_FUNCTIONS_H
#define TT_FUNCTIONS_H

#include "data.h"

// Vector

struct TTVector tt_vector_init(unsigned int rows);
void tt_vector_delete(struct TTVector* v);

float* tt_vector_get_data(struct TTVector* v, unsigned int rid);

// Layer

float* tt_layer_get_weight(struct TTLayer* l, unsigned int rid,
                           unsigned int cid);
float* tt_layer_get_bias(struct TTLayer* l, unsigned int rid);

// Block

struct TTBlock tt_block_init(unsigned int layers_count,
                             unsigned int* layer_input_sizes,
                             unsigned int output_size);
void tt_block_delete(struct TTBlock* b);

unsigned int tt_block_get_in_size(struct TTBlock* b);
unsigned int tt_block_get_out_size(struct TTBlock* b);

int tt_block_transform(struct TTBlock* b, struct TTVector* vin,
                       struct TTVector* vout);

// File interface

int tt_block2file(struct TTBlock* b, char* file);
int tt_file2block(struct TTBlock* b, char* file);

// Simple Back propagation

int tt_sbp_error_propagate(struct TTBlock* b, struct TTVector* vin,
                           struct TTVector* vexp,
                           float max_change_in_error_squared);

#endif
