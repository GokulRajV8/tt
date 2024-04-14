#include "tt.h"

void test1() {
    int result;
    float m1_values[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
    float m2_values[9] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Matrix m1 = matx_init_data(3, 3, m1_values);
    matx_print(&m1, "m1");

    Matrix m2 = matx_init_data(3, 3, m2_values);
    matx_print(&m2, "m2");

    Matrix m3 = matx_init_bare(3, 3);

    result = matx_add(&m1, &m2, &m3);
    if (result == 0)
        matx_print(&m3, "m1 + m2");
    else
        fprintf(stdout, "Addition failed");

    result = matx_sub(&m1, &m2, &m3);
    if (result == 0)
        matx_print(&m3, "m1 - m2");
    else
        fprintf(stdout, "Subtraction failed");

    result = matx_matx_prod(&m1, &m2, &m3);
    if (result == 0)
        matx_print(&m3, "m1 * m2");
    else
        fprintf(stdout, "Multiplication failed");

    // deletion
    matx_delete(&m1);
    matx_delete(&m2);
    matx_delete(&m3);
}

void test2() {
    int result;
    float v1_values[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
    float v2_values[9] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Vector v1 = vect_init_data(9, v1_values);
    vect_print(&v1, "v1");

    Vector v2 = vect_init_data(9, v2_values);
    vect_print(&v2, "v2");

    Vector v3 = vect_init_bare(9);

    result = vect_add(&v1, &v2, &v3);
    if (result == 0)
        vect_print(&v3, "v1 + v2");
    else
        fprintf(stdout, "Addition failed");

    result = vect_sub(&v1, &v2, &v3);
    if (result == 0)
        vect_print(&v3, "v1 - v2");
    else
        fprintf(stdout, "Subtraction failed");

    float prod;
    result = vect_vect_prod(&v1, &v2, &prod);
    if (result == 0)
        fprintf(stdout, "v1 * v2 : %f\n", prod);
    else
        fprintf(stdout, "Multiplication failed");

    float m_values[18] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0,
                          1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Matrix m = matx_init_data(2, 9, m_values);
    matx_print(&m, "m");

    Vector v4 = vect_init_bare(2);

    result = matx_vect_prod(&m, &v1, &v4);
    if (result == 0)
        vect_print(&v4, "m * v1");
    else
        fprintf(stdout, "Multiplication failed");

    // deletion
    vect_delete(&v1);
    vect_delete(&v2);
    vect_delete(&v3);
    vect_delete(&v4);
    matx_delete(&m);
}

void test3() {
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
}

int main() {
    fprintf(stdout, "Test 1 >>\n");
    test1();

    fprintf(stdout, "Test 2 >>\n");
    test2();

    fprintf(stdout, "Test 3 >>\n");
    test3();

    return 0;
}
