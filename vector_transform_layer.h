#ifndef VECTOR_TRANSFORM_LAYER_H_
#define VECTOR_TRANSFORM_LAYER_H_

#include "common.h"
#include "matrix.h"
#include "vector.h"

/*
 * data types
 */

struct VectorTransformLayer {
    struct Matrix weights;
    struct Vector bias;
    uint32_t in_size;
    uint32_t out_size;
};

/*
 * functions
 */

struct VectorTransformLayer vtl_init(uint32_t in_size, uint32_t out_size,
                                     float* data);
void vtl_delete(struct VectorTransformLayer* vtl);

int vtl_transform(struct VectorTransformLayer* vtl, struct Vector* vin,
                  struct Vector* vout);

#endif
