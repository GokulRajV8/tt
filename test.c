#include "tt.h"

int main() {
    int result;
    float vtl_values[8] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0};

    VectorTransformLayer vtl = vtl_init(3, 2, vtl_values);

    float vin_values[3] = {1.0, 2.0, 3.0};

    Vector vin = vect_init_data(3, vin_values);
    vect_print(&vin, "vin");

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

    return 0;
}
