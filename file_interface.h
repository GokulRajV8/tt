#ifndef FILE_INTERFACE_H_
#define FILE_INTERFACE_H_

#define MAX_FILE_LINE_LENGTH 16 * 1024 * 1024

#include "common.h"
#include "matrix.h"
#include "vector.h"
#include "vector_transform_block.h"

/*
 * data types
 */

struct VTBFileData {
    uint32_t layers_count;
    char** layers_data;
};

/*
 * functions
 */

struct VTBFileData vtb_read(FILE* f);
void vtb_dump(FILE* f, struct VectorTransformBlock* vtb);
void vtb_file_data_delete(struct VTBFileData* vtb_file_data);

#endif
