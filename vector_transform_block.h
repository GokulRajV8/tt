#ifndef VECTOR_TRANSFORM_BLOCK_H_
#define VECTOR_TRANSFORM_BLOCK_H_

#include <stdint.h>

#include "vector_transform_layer.h"

/*
 * data types
 */

struct VectorTransformBlock {
    struct VectorTransformLayer* layers;
    uint32_t layers_count;
};

/*
 * functions
 */

struct VectorTransformBlock vtb_init(uint32_t layers_count,
                                     uint32_t* layer_input_size,
                                     uint32_t output_size, float** values);
void vtb_delete(struct VectorTransformBlock* vtb);

int vtb_transform(struct VectorTransformBlock* vtb, struct Vector* vin,
                  struct Vector* vout);

#endif
