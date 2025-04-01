#include <stdio.h>
#include <stdlib.h>

#include "tt/data.h"
#include "tt/functions.h"

static void populate_tt_block(struct TTBlock* b) {
    for (unsigned int layer_id = 0; layer_id < b->layers_count; ++layer_id) {
        struct TTLayer curr_layer = b->layers[layer_id];
        float weight = 1.0f / curr_layer.in_size;

        for (unsigned int rid = 0; rid < curr_layer.out_size; ++rid) {
            for (unsigned int cid = 0; cid < curr_layer.in_size; ++cid)
                *tt_layer_get_weight(&curr_layer, rid, cid) = weight;
            *tt_layer_get_bias(&curr_layer, rid) = 0.0f;
        }
    }
}

static void test1() {
    unsigned int layers_count = 2;
    unsigned int* layer_input_sizes =
        malloc(sizeof(unsigned int) * layers_count);
    layer_input_sizes[0] = 5;
    layer_input_sizes[1] = 10;
    unsigned int output_size = 5;

    struct TTBlock b =
        tt_block_init(layers_count, layer_input_sizes, output_size);
    free(layer_input_sizes);

    populate_tt_block(&b);
    int result = tt_block2file(&b, "blk_test");
    if (result != 0) perror("Unable to save to file");

    tt_block_delete(&b);
}

static void test2() {
    struct TTBlock b = {.layers = NULL};

    int result = tt_file2block(&b, "blk_test");
    if (result != 0) {
        perror("Unable to read from file");
        exit(1);
    }

    struct TTVector vin = tt_vector_init(tt_block_get_in_size(&b));
    struct TTVector vout = tt_vector_init(tt_block_get_out_size(&b));
    for (unsigned int i = 0; i < vin.rows; ++i) {
        fprintf(stdout, "Enter the value of input at row %d : ", i);
        fscanf(stdin, "%f", tt_vector_get_data(&vin, i));
    }

    result = tt_block_transform(&b, &vin, &vout);
    if (result == 0)
        for (unsigned int i = 0; i < vout.rows; ++i)
            fprintf(stdout, "%f\n", vout.data[i]);
    else
        perror("Calculations failed");

    tt_vector_delete(&vout);
    tt_vector_delete(&vin);
    tt_block_delete(&b);
}

static void test3() {
    struct TTBlock b = {.layers = NULL};

    int result = tt_file2block(&b, "blk_test");
    if (result != 0) {
        perror("Unable to read from file");
        exit(1);
    }

    struct TTVector vin = tt_vector_init(tt_block_get_in_size(&b));
    struct TTVector vexp = tt_vector_init(tt_block_get_out_size(&b));

    unsigned int total_epochs;
    fscanf(stdin, "%d", &total_epochs);
    float max_change_in_error_squared;
    fscanf(stdin, "%f", &max_change_in_error_squared);
    for (unsigned int rid = 0; rid < vin.rows; ++rid)
        fscanf(stdin, "%f", tt_vector_get_data(&vin, rid));
    for (unsigned int rid = 0; rid < vexp.rows; ++rid)
        fscanf(stdin, "%f", tt_vector_get_data(&vexp, rid));

    struct TTVector vout = tt_vector_init(tt_block_get_out_size(&b));
    for (unsigned int epoch = 0; epoch < total_epochs; ++epoch) {
        tt_sbp_error_propagate(&b, &vin, &vexp, max_change_in_error_squared);
        tt_block_transform(&b, &vin, &vout);
    }
    tt_vector_delete(&vout);

    tt_vector_delete(&vexp);
    tt_vector_delete(&vin);
    tt_block_delete(&b);
}

int main() {
    int option;
    fscanf(stdin, "%d", &option);

    switch (option) {
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        default:
            perror("Invalid option");
    }

    return 0;
}
