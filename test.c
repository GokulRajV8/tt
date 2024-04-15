#include "tt.h"

int main() {
    int result;

    // -- Testing Vector transform layer --

    float vtl_values[8] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0};

    VectorTransformLayer vtl = vtl_init(3, 2, vtl_values);

    float vin_values[3] = {1.0, 2.0, 3.0};

    Vector vin = vect_init_data(3, vin_values);
    vect_print(&vin, "vin for layer");

    Vector vout = vect_init_bare(2);

    result = vtl_transform(&vtl, &vin, &vout);
    if (result == 0)
        vect_print(&vout, "vtl(vin)");
    else
        fprintf(stdout, "Transformation failed");

    // deletion
    vtl_delete(&vtl);
    vect_delete(&vin);
    vect_delete(&vout);

    // -- Testing Vector transform block --

    float vin1_values[3] = {1.0, 2.0, 3.0};

    Vector vin1 = vect_init_data(3, vin1_values);
    vect_print(&vin, "vin for block");

    uint32_t input_size[2] = {3, 2};
    float vtb_layer1_values[8] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0};
    float vtb_layer2_values[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    float* vtb_values[2] = {vtb_layer1_values, vtb_layer2_values};
    VectorTransformBlock vtb = vtb_init(2, input_size, 3, vtb_values);

    Vector vout1 = vect_init_bare(3);

    result = vtb_transform(&vtb, &vin1, &vout1);
    if (result == 0)
        vect_print(&vout1, "vtb(vin)");
    else
        fprintf(stdout, "Transformation failed");

    // deletion
    vtb_delete(&vtb);
    vect_delete(&vin1);
    vect_delete(&vout1);

    return 0;
}
