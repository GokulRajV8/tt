#ifndef VECTOR_TRANSFORM_BLOCK_CREATOR_H_
#define VECTOR_TRANSFORM_BLOCK_CREATOR_H_

#include "common.h"
#include "vector_transform_block.h"

/*
 * functions
 */

struct VectorTransformBlock vtb_create(uint32_t layers_count,
                                       char** layers_data);
struct VectorTransformBlock avg_vtb_create(uint32_t layers_count,
                                           uint32_t* input_sizes,
                                           uint32_t output_size);

#endif
