// Contains all the data structures exposed by TT library

#ifndef TT_DATA_H
#define TT_DATA_H

// Math objects

struct TTVector {
    unsigned int rows;
    float* data;
};

struct TTMatrix {
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
    unsigned int layers_count;
    struct TTLayer* layers;
};

#endif
