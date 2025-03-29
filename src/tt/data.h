// Contains all the data structures exposed by TT library

#ifndef TT_DATA_H
#define TT_DATA_H

#include <stdbool.h>

// Math objects

struct TTVector {
    bool is_empty;
    unsigned int rows;
    float* data;
};

struct TTMatrix {
    bool is_empty;
    unsigned int rows;
    unsigned int cols;
    float* data;
};

// Transformer objects

struct TTLayer {
    unsigned int in_size;
    unsigned int out_size;
    struct TTMatrix weights;
    struct TTVector bias;
};

struct TTBlock {
    bool is_empty;
    unsigned int layers_count;
    struct TTLayer* layers;
};

#endif
