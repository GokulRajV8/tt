#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "functions.h"
#include "idata.h"
#include "ifunctions.h"

struct TTBlock tt_block_init(unsigned int layers_count,
                             unsigned int* layer_input_sizes,
                             unsigned int output_size) {
    struct TTBlock b;
    b.layers_count = layers_count;
    b.layers = malloc(sizeof(struct TTLayer) * layers_count);

    for (unsigned int layer_id = 0; layer_id < layers_count; ++layer_id) {
        struct TTLayer* curr_layer = &b.layers[layer_id];
        curr_layer->in_size = layer_input_sizes[layer_id];
        curr_layer->out_size = (layer_id < layers_count - 1)
                                   ? layer_input_sizes[layer_id + 1]
                                   : output_size;

        curr_layer->weights =
            matrix_init(curr_layer->out_size, curr_layer->in_size);
        curr_layer->bias = tt_vector_init(curr_layer->out_size);
    }

    return b;
}

void tt_block_delete(struct TTBlock* b) {
    if (b->layers != NULL) {
        for (unsigned int layer_id = 0; layer_id < b->layers_count;
             ++layer_id) {
            struct TTLayer curr_layer = b->layers[layer_id];
            matrix_delete(&curr_layer.weights);
            tt_vector_delete(&curr_layer.bias);
        }
        free(b->layers);
        b->layers = NULL;
    }
}

unsigned int tt_block_get_in_size(struct TTBlock* b) {
    return b->layers[0].in_size;
}

unsigned int tt_block_get_out_size(struct TTBlock* b) {
    return b->layers[b->layers_count - 1].out_size;
}

int tt_block_transform(struct TTBlock* b, struct TTVector* vin,
                       struct TTVector* vout) {
    // checking input and output dimensions
    if (b->layers[0].in_size != vin->rows ||
        b->layers[b->layers_count - 1].out_size != vout->rows)
        return -1;

    // copying vin into temp_vector
    struct TTVector temp_vector = tt_vector_init(vin->rows);
    memcpy(temp_vector.data, vin->data, sizeof(float) * vin->rows);

    for (unsigned int layer_id = 0; layer_id < b->layers_count; ++layer_id) {
        struct TTLayer curr_layer = b->layers[layer_id];

        // calculating transform of temp_vector and storing in vout
        vector_resize(vout, curr_layer.out_size);
        layer_transform(&curr_layer, &temp_vector, vout);

        // copying vout into temp_vector
        vector_resize(&temp_vector, vout->rows);
        memcpy(temp_vector.data, vout->data, sizeof(float) * vout->rows);
    }

    tt_vector_delete(&temp_vector);
    return 0;
}

struct GranularLayerInput block_transform_granular(struct TTBlock* b,
                                                   struct TTVector* vin,
                                                   struct TTVector* vout) {
    struct GranularLayerInput gli = {.was_successful = false, .inputs = NULL};

    // checking input and output dimensions
    if (b->layers[0].in_size != vin->rows ||
        b->layers[b->layers_count - 1].out_size != vout->rows)
        return gli;

    unsigned int* input_sizes = malloc(sizeof(unsigned int) * b->layers_count);
    for (unsigned int i = 0; i < b->layers_count; ++i)
        input_sizes[i] = b->layers[i].in_size;
    gli.inputs = vector_list_init(b->layers_count, input_sizes);
    free(input_sizes);

    unsigned int curr_layer_id = 0;

    // copying vin into first layer input vector
    memcpy(gli.inputs[curr_layer_id].data, vin->data,
           sizeof(float) * vin->rows);

    for (; curr_layer_id < b->layers_count;) {
        struct TTLayer curr_layer = b->layers[curr_layer_id];

        // calculating transform of curr_layer input and storing in vout
        vector_resize(vout, curr_layer.out_size);
        layer_transform(&curr_layer, gli.inputs + curr_layer_id, vout);

        // copying vout into next layer input if present
        if (++curr_layer_id < b->layers_count)
            memcpy(gli.inputs[curr_layer_id].data, vout->data,
                   sizeof(float) * vout->rows);
    }

    gli.was_successful = true;
    return gli;
}
