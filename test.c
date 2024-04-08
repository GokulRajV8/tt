#include "tt.h"

void test1() {
    int result;
    float m1_values[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
    float m2_values[9] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Matrix m1 = matx_init_data(3, 3, m1_values);
    matx_print(&m1);

    Matrix m2 = matx_init_data(3, 3, m2_values);
    matx_print(&m2);

    Matrix m3 = matx_init_bare(3, 3);

    result = matx_add(&m1, &m2, &m3);
    if (result == 0) {
        fprintf(stdout, "Addition result");
        matx_print(&m3);
    } else {
        fprintf(stdout, "Addition failed");
    }

    result = matx_sub(&m1, &m2, &m3);
    if (result == 0) {
        fprintf(stdout, "Subtraction result");
        matx_print(&m3);
    } else {
        fprintf(stdout, "Subtraction failed");
    }

    result = matx_matx_prod(&m1, &m2, &m3);
    if (result == 0) {
        fprintf(stdout, "Multiplication result");
        matx_print(&m3);
    } else {
        fprintf(stdout, "Multiplication failed");
    }
}

void test2() {
    int result;
    float v1_values[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
    float v2_values[9] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Vector v1 = vect_init_data(9, v1_values);
    vect_print(&v1);

    Vector v2 = vect_init_data(9, v2_values);
    vect_print(&v2);

    Vector v3 = vect_init_bare(9);

    result = vect_add(&v1, &v2, &v3);
    if (result == 0) {
        fprintf(stdout, "Addition result");
        vect_print(&v3);
    } else {
        fprintf(stdout, "Addition failed");
    }

    result = vect_sub(&v1, &v2, &v3);
    if (result == 0) {
        fprintf(stdout, "Subtraction result");
        vect_print(&v3);
    } else {
        fprintf(stdout, "Subtraction failed");
    }

    float prod;
    result = vect_vect_prod(&v1, &v2, &prod);
    if (result == 0) {
        fprintf(stdout, "Multiplication result : %f\n", prod);
    } else {
        fprintf(stdout, "Multiplication failed");
    }

    float m_values[18] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0,
                          1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Matrix m = matx_init_data(2, 9, m_values);
    matx_print(&m);

    Vector v4 = vect_init_bare(2);

    result = matx_vect_prod(&m, &v1, &v4);
    if (result == 0) {
        fprintf(stdout, "Multiplication result");
        vect_print(&v4);
    } else {
        fprintf(stdout, "Multiplication failed");
    }
}

int main() {
    fprintf(stdout, "Test 1 >>\n");
    test1();

    fprintf(stdout, "Test 2 >>\n");
    test2();

    return 0;
}
