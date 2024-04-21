#include "tt.h"

int main() {
    int result;

    // -- Testing Vector transform layer --

    float vin_for_vtl_values[3] = {1.0, 2.0, 3.0};
    struct Vector vin_for_vtl = vect_init_data(3, vin_for_vtl_values);
    vect_print(&vin_for_vtl, "vin for layer");

    float vtl_values[8] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0};
    struct VectorTransformLayer vtl = vtl_init(3, 2, vtl_values);

    struct Vector vout_for_vtl = vect_init_bare(2);

    result = vtl_transform(&vtl, &vin_for_vtl, &vout_for_vtl);
    if (result == 0)
        vect_print(&vout_for_vtl, "vtl(vin)");
    else
        fprintf(stdout, "Transformation failed");

    // deletion
    vtl_delete(&vtl);
    vect_delete(&vin_for_vtl);
    vect_delete(&vout_for_vtl);

    // -- Testing Vector transform block --

    float vin_for_vtb_values[3] = {1.0, 2.0, 3.0};
    struct Vector vin_for_vtb = vect_init_data(3, vin_for_vtb_values);
    vect_print(&vin_for_vtb, "vin for block");

    uint32_t input_size[2] = {3, 2};
    float vtb_layer1_values[8] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0};
    float vtb_layer2_values[9] = {1.0,  3.0,  5.0,  7.0, 9.0,
                                  11.0, 13.0, 15.0, 17.0};
    float* vtb_values[2] = {vtb_layer1_values, vtb_layer2_values};
    struct VectorTransformBlock vtb = vtb_init(2, input_size, 3, vtb_values);

    struct Vector vout_for_vtb = vect_init_bare(3);

    result = vtb_transform(&vtb, &vin_for_vtb, &vout_for_vtb);
    if (result == 0)
        vect_print(&vout_for_vtb, "vtb(vin)");
    else
        fprintf(stdout, "Transformation failed");

    // deletion
    vtb_delete(&vtb);
    vect_delete(&vin_for_vtb);
    vect_delete(&vout_for_vtb);

    // -- Testing Vector transform block creator --

    float vin_for_vtbc_values[3] = {1.0, 2.0, 3.0};
    struct Vector vin_for_vtbc = vect_init_data(3, vin_for_vtbc_values);
    vect_print(&vin_for_vtbc, "vin for block creator");

    char* input_for_vtbc[2] = {"3 2\n0.0 2.0 4.0 6.0 8.0 10.0 12.0 14.0",
                               "2 3\n1.0 3.0 5.0 7.0 9.0 11.0 13.0 15.0 17.0"};
    struct VectorTransformBlock vtb_for_vtbc = vtb_create(2, input_for_vtbc);

    struct Vector vout_for_vtbc = vect_init_bare(3);

    result = vtb_transform(&vtb_for_vtbc, &vin_for_vtbc, &vout_for_vtbc);
    if (result == 0)
        vect_print(&vout_for_vtbc, "vtb_for_vtbc(vin)");
    else
        fprintf(stdout, "Transformation failed");

    // deletion
    vtb_delete(&vtb_for_vtbc);
    vect_delete(&vin_for_vtbc);
    vect_delete(&vout_for_vtbc);

    return 0;
}
