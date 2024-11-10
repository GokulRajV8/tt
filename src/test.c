#include "common.h"
#include "tt.h"

int main() {
    int result;

    // creating vtb
    uint32_t input_sizes[8] = {10, 60, 40, 50, 30, 20, 50, 60};
    struct VectorTransformBlock vtb = avg_vtb_create(8, input_sizes, 30);
    fprintf(stdout, "VTB created");

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
    struct Vector vout = vect_init_bare(30);

    // transforming and result display
    result = vtb_transform(&vtb, &vin, &vout);
    if (result == 0)
        vect_print(&vout, "vtb(vin)");
    else
        fprintf(stdout, "\nTransformation failed");

    // dumping vtb created
    FILE* vtb_file_to_write;
    vtb_file_to_write = fopen("avg_vtb1.txt", "w");
    assert(vtb_file_to_write != NULL);
    vtb_dump(vtb_file_to_write, &vtb);
    fprintf(stdout, "\nVTB file created successfully");
    fclose(vtb_file_to_write);

    // deletion
    vtb_delete(&vtb);
    vect_delete(&vin);
    vect_delete(&vout);

    return 0;
}
