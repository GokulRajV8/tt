#include "file_interface.h"

// static methods

static uint32_t get_output_size(char* dimensions_line) {
    uint32_t index = 0;
    while (dimensions_line[index] != ' ') ++index;
    return atol(dimensions_line + index + 1);
}

static char* concat_with_newline(char* str1, char* str2) {
    uint32_t str1_len = 0;
    while (*(str1 + str1_len) != '\0') ++str1_len;

    uint32_t str2_len = 0;
    while (*(str2 + str2_len) != '\0') ++str2_len;

    char* str_temp = malloc(sizeof(char) * (str1_len + str2_len + 2));
    memcpy(str_temp, str1, sizeof(char) * str1_len);
    str_temp[str1_len] = '\n';
    memcpy(str_temp + str1_len + 1, str2, sizeof(char) * str2_len);
    str_temp[str1_len + 1 + str2_len] = '\0';

    free(str1);
    free(str2);

    return str_temp;
}

// methods

struct VTBFileData vtb_read(FILE* f) {
    struct VTBFileData vtb_file_data;
    char* file_line = malloc(sizeof(char) * MAX_FILE_LINE_LENGTH);
    char* empty_line = malloc(sizeof(char) * 2);

    fgets(file_line, MAX_FILE_LINE_LENGTH, f);
    vtb_file_data.layers_count = atol(file_line);
    vtb_file_data.layers_data =
        malloc(sizeof(char*) * vtb_file_data.layers_count);

    char* layer_data;
    for (uint32_t layer_id = 0; layer_id < vtb_file_data.layers_count;
         ++layer_id) {
        fgets(empty_line, 2, f);

        // dimensions
        fgets(file_line, MAX_FILE_LINE_LENGTH, f);
        uint32_t dimensions_line_len = strlen(file_line) - 1;
        char* dimensions_line = malloc(sizeof(char) * dimensions_line_len + 1);
        memcpy(dimensions_line, file_line, sizeof(char) * dimensions_line_len);
        dimensions_line[dimensions_line_len] = '\0';

        // float data
        uint32_t output_size = get_output_size(dimensions_line);
        for (uint32_t i = 0; i <= output_size; ++i) {
            fgets(file_line, MAX_FILE_LINE_LENGTH, f);
            uint32_t float_data_line_len = strlen(file_line) - 1;
            char* float_data_line =
                malloc(sizeof(char) * float_data_line_len + 1);
            memcpy(float_data_line, file_line,
                   sizeof(char) * float_data_line_len);
            float_data_line[float_data_line_len] = '\0';

            // concatenating
            dimensions_line =
                concat_with_newline(dimensions_line, float_data_line);
        }

        // addding data to vtb_file_data
        vtb_file_data.layers_data[layer_id] = dimensions_line;
    }

    // freeing memory
    free(file_line);
    free(empty_line);

    return vtb_file_data;
}

void vtb_dump(FILE* f, struct VectorTransformBlock vtb) {}

void avg_vtb_creator(FILE* f, uint32_t layer_count, uint32_t* input_sizes,
                     uint32_t output_size) {
    // number of layers
    fprintf(f, "%d", layer_count);

    uint32_t layer_input, layer_output;
    for (uint32_t layer_id = 0; layer_id < layer_count; ++layer_id) {
        layer_input = input_sizes[layer_id];
        if (layer_id != layer_count - 1)
            layer_output = input_sizes[layer_id + 1];
        else
            layer_output = output_size;

        // layer dimensions
        fprintf(f, "\n\n%d %d", layer_input, layer_output);

        // float data
        float float_value;
        for (uint32_t i = 0; i <= layer_output; ++i) {
            if (i == layer_output) {
                float_value = 0.0f;
                fprintf(f, "\n%f", float_value);
                for (uint32_t j = 1; j < layer_output; ++j)
                    fprintf(f, " %f", float_value);
            } else {
                float_value = 1.0f / layer_input;
                fprintf(f, "\n%f", float_value);
                for (uint32_t j = 1; j < layer_input; ++j)
                    fprintf(f, " %f", float_value);
            }
        }
    }
}

void vtb_file_data_delete(struct VTBFileData* vtb_file_data) {
    for (uint32_t layer_id = 0; layer_id < vtb_file_data->layers_count;
         ++layer_id)
        free(vtb_file_data->layers_data[layer_id]);
    free(vtb_file_data->layers_data);
}
