#ifndef FILE_INTERFACE_H_
#define FILE_INTERFACE_H_

#define MAX_FILE_LINE_LENGTH 16 * 1024 * 1024

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
void vtb_dump(FILE* f, struct VectorTransformBlock vtb);
void avg_vtb_creator(FILE* f, uint32_t* input_sizes, uint32_t output_size);

void vtb_file_data_delete(struct VTBFileData* vtb_file_data);

#endif
