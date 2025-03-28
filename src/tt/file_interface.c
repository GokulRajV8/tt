#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "functions.h"

int tt_block2file(struct TTBlock* b, char* file) {
    FILE* f = fopen(file, "wb");
    if (f == NULL) {
        fprintf(stdout, "Unable to open given file");
        return -1;
    }

    // writing layers_count, input sizes and output size
    fwrite(&b->layers_count, sizeof(unsigned int), 1, f);
    unsigned int layer_id = 0;
    for (; layer_id < b->layers_count; ++layer_id)
        fwrite(&b->layers[layer_id].in_size, sizeof(unsigned int), 1, f);
    fwrite(&b->layers[layer_id - 1].out_size, sizeof(unsigned int), 1, f);

    // writing weights and biases data
    layer_id = 0;
    for (; layer_id < b->layers_count; ++layer_id) {
        fwrite(b->layers[layer_id].weights.data, sizeof(float),
               b->layers[layer_id].in_size * b->layers[layer_id].out_size, f);
        fwrite(b->layers[layer_id].bias.data, sizeof(float),
               b->layers[layer_id].out_size, f);
    }

    fclose(f);
    return 0;
}

struct TTBlock tt_file2block(char* file) {
    FILE* f = fopen(file, "rb");
    if (f == NULL) {
        fprintf(stdout, "Unable to open given file");
        exit(1);
    }

    // reading layers_count, input sizes and output size
    unsigned int layers_count;
    fread(&layers_count, sizeof(unsigned int), 1, f);
    unsigned int* layer_input_sizes =
        malloc(sizeof(unsigned int) * layers_count);
    fread(layer_input_sizes, sizeof(unsigned int), layers_count, f);
    unsigned int output_size;
    fread(&output_size, sizeof(unsigned int), 1, f);

    struct TTBlock b =
        tt_block_init(layers_count, layer_input_sizes, output_size);

    // reading weights and biases data
    for (unsigned int layer_id = 0; layer_id < layers_count; ++layer_id) {
        struct TTLayer curr_layer = b.layers[layer_id];
        fread(curr_layer.weights.data, sizeof(float),
              curr_layer.in_size * curr_layer.out_size, f);
        fread(curr_layer.bias.data, sizeof(float), curr_layer.out_size, f);
    }

    free(layer_input_sizes);
    fclose(f);

    return b;
}
