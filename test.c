#include "common.h"
#include "tt.h"

int main() {
    int result;

    // creating VTB file
    FILE* vtb_file_to_write = fopen("test\\avg_vtb1.txt", "w");
    assert(vtb_file_to_write != NULL);

    uint32_t input_sizes[5] = {12, 20, 40, 40, 20};
    avg_vtb_creator(vtb_file_to_write, 5, input_sizes, 12);
    fprintf(stdout, "\nVTB file created successfully");
    fclose(vtb_file_to_write);

    // reading vtb file
    FILE* vtb_file = fopen("test\\avg_vtb1.txt", "r");
    assert(vtb_file != NULL);
    struct VTBFileData vtb_file_data = vtb_read(vtb_file);
    fprintf(stdout, "\nVTB file read");
    fclose(vtb_file);

    // creating vtb
    struct VectorTransformBlock vtb =
        vtb_create(vtb_file_data.layers_count, vtb_file_data.layers_data);
    fprintf(stdout, "\nVTB created");
    vtb_file_data_delete(&vtb_file_data);

    // creating vin
    uint32_t input_size = vtb.layers[0].in_size;
    float* vin_values = malloc(sizeof(float) * input_size);
    fprintf(stdout, "\nEnter %d values :\n", input_size);
    for (uint32_t i = 0; i < input_size; ++i)
        fscanf(stdin, "%f", vin_values + i);
    struct Vector vin = vect_init_data(input_size, vin_values);
    free(vin_values);
    vect_print(&vin, "vin");

    // creating vout
    struct Vector vout = vect_init_bare(12);

    // transforming and result display
    result = vtb_transform(&vtb, &vin, &vout);
    if (result == 0)
        vect_print(&vout, "vtb(vin)");
    else
        fprintf(stdout, "\nTransformation failed");

    // deletion
    vtb_delete(&vtb);
    vect_delete(&vin);
    vect_delete(&vout);

    return 0;
}
