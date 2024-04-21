#include "tt.h"

int main() {
    int result;

    float vin_values[3] = {1.0, 2.0, 3.0};
    struct Vector vin = vect_init_data(3, vin_values);
    vect_print(&vin, "vin");

    char* input_for_vtb[2] = {"3 2\n0.0 2.0 4.0 6.0 8.0 10.0 12.0 14.0",
                              "2 3\n1.0 3.0 5.0 7.0 9.0 11.0 13.0 15.0 17.0"};
    struct VectorTransformBlock vtb = vtb_create(2, input_for_vtb);

    struct Vector vout = vect_init_bare(3);

    result = vtb_transform(&vtb, &vin, &vout);
    if (result == 0)
        vect_print(&vout, "vtb(vin)");
    else
        fprintf(stdout, "Transformation failed");

    // deletion
    vtb_delete(&vtb);
    vect_delete(&vin);
    vect_delete(&vout);

    return 0;
}
