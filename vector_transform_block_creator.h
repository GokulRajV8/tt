#ifndef VECTOR_TRANSFORM_BLOCK_CREATOR_H_
#define VECTOR_TRANSFORM_BLOCK_CREATOR_H_

#include <assert.h>

#include "vector_transform_block.h"

struct VectorTransformBlock vtb_create(uint32_t layer_count, char** layer_data);

#endif
