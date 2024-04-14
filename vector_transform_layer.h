#ifndef VECTOR_TRANSFORM_LAYER_H_
#define VECTOR_TRANSFORM_LAYER_H_

#include <stdint.h>

#include "matrix.h"
#include "vector.h"

/*
 * data types
 */

typedef struct {
    Matrix weights;
    Vector bias;
    uint32_t in_size;
    uint32_t out_size;
} VectorTransformLayer;

/*
 * functions
 */

VectorTransformLayer vtl_init(uint32_t in_size, uint32_t out_size, float* data);
void vtl_delete(VectorTransformLayer* vtl);

int vtl_transform(VectorTransformLayer* vtl, Vector* vin, Vector* vout);

#endif
