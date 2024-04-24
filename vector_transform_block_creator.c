#include "vector_transform_block_creator.h"

// static methods

static uint32_t substring_count(char* input_str, char delimiter) {
    uint32_t substring_count = 1;
    for (char* cursor = input_str; *cursor != '\0'; ++cursor)
        if (*cursor == delimiter) ++substring_count;
    return substring_count;
}

static char** split(char* input_str, char delimiter) {
    char* start = input_str;
    char* end = input_str;

    uint32_t substrings_in_input = substring_count(input_str, delimiter);
    char** output = malloc(sizeof(char*) * substrings_in_input);
    memset(output, 0, sizeof(char*) * substrings_in_input);

    uint32_t output_index = 0;
    uint32_t substring_len = 0;
    while (output_index < substrings_in_input) {
        if (*end == delimiter || *end == '\0') {
            substring_len = end - start;
            output[output_index] = malloc(sizeof(char) * (substring_len + 1));
            memcpy(output[output_index], start, sizeof(char) * substring_len);
            output[output_index][substring_len] = '\0';
            ++output_index;

            start = ++end;
        } else
            ++end;
    }

    return output;
}

static void delete_list_of_blocks(uint32_t block_count, void** list_of_blocks) {
    for (uint32_t block_id = 0; block_id < block_count; ++block_id)
        free(list_of_blocks[block_id]);
    free(list_of_blocks);
}

// methods

struct VectorTransformBlock vtb_create(uint32_t layers_count,
                                       char** layers_data) {
    uint32_t input_size;
    uint32_t output_size;
    uint32_t* layer_input_size = malloc(sizeof(uint32_t) * layers_count);
    float** layer_float_data = malloc(sizeof(float*) * layers_count);

    for (uint32_t layer_id = 0; layer_id < layers_count; ++layer_id) {
        char** dimensions_and_floats_str = split(layers_data[layer_id], '\n');

        assert(substring_count(dimensions_and_floats_str[0], ' ') == 2);
        char** dimensions_str = split(dimensions_and_floats_str[0], ' ');
        input_size = atol(dimensions_str[0]);

        if (layer_id > 0) assert(output_size == input_size);
        layer_input_size[layer_id] = input_size;

        output_size = atol(dimensions_str[1]);

        assert(substring_count(layers_data[layer_id], '\n') ==
               (output_size + 2));

        layer_float_data[layer_id] =
            malloc(sizeof(float) * ((input_size + 1) * output_size));
        char** floats_str;
        for (uint32_t line = 1; line < (output_size + 2); ++line) {
            if (line != (output_size + 1)) {
                assert(substring_count(dimensions_and_floats_str[line], ' ') ==
                       input_size);
                floats_str = split(dimensions_and_floats_str[line], ' ');
                for (uint32_t i = 0; i < input_size; ++i)
                    layer_float_data[layer_id][((line - 1) * input_size) + i] =
                        atof(floats_str[i]);
                delete_list_of_blocks(input_size, floats_str);
            } else {
                assert(substring_count(dimensions_and_floats_str[line], ' ') ==
                       output_size);
                floats_str = split(dimensions_and_floats_str[line], ' ');
                for (uint32_t i = 0; i < output_size; ++i)
                    layer_float_data[layer_id][((line - 1) * input_size) + i] =
                        atof(floats_str[i]);
                delete_list_of_blocks(output_size, floats_str);
            }
        }

        // freeing memory
        delete_list_of_blocks(2, dimensions_str);
        delete_list_of_blocks(2, dimensions_and_floats_str);
    }

    struct VectorTransformBlock vtb =
        vtb_init(layers_count, layer_input_size, output_size, layer_float_data);

    // freeing memory
    free(layer_input_size);
    delete_list_of_blocks(layers_count, layer_float_data);

    return vtb;
}

struct VectorTransformBlock avg_vtb_create(uint32_t layers_count,
                                           uint32_t* input_sizes,
                                           uint32_t output_size) {
    float** layer_float_data = malloc(sizeof(float*) * layers_count);

    uint32_t layer_input_size, layer_output_size;
    for (uint32_t layer_id = 0; layer_id < layers_count; ++layer_id) {
        layer_input_size = input_sizes[layer_id];
        if (layer_id != layers_count - 1)
            layer_output_size = input_sizes[layer_id + 1];
        else
            layer_output_size = output_size;

        layer_float_data[layer_id] = malloc(
            sizeof(float) * ((layer_input_size + 1) * layer_output_size));

        // setting weights
        for (uint32_t i = 0; i < (layer_input_size * layer_output_size); ++i)
            layer_float_data[layer_id][i] = 1.0f / layer_input_size;

        // setting biases
        for (uint32_t i = 0; i < layer_output_size; ++i)
            layer_float_data[layer_id]
                            [layer_input_size * layer_output_size + i] = 0.0f;
    }

    struct VectorTransformBlock vtb =
        vtb_init(layers_count, input_sizes, output_size, layer_float_data);

    delete_list_of_blocks(layers_count, layer_float_data);

    return vtb;
}
