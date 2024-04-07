#include <stdio.h>

#include "matrix.h"

void print(Matrix* m) {
    fprintf(stdout, "\nRows : %d", m->rows);
    fprintf(stdout, "\nColumns : %d", m->columns);

    fprintf(stdout, "\nValues ->\n");
    for (int row_id = 0; row_id < m->rows; ++row_id) {
        fprintf(stdout, "[");
        for (int column_id = 0; column_id < m->columns; ++column_id)
            fprintf(stdout, "%3.2f, ",
                    *(m->values + (row_id * m->columns) + column_id));
        fprintf(stdout, "]\n");
    }
}

int main() {
    int result;
    float values_1[9] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
    float values_2[9] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

    Matrix m1;
    m1.rows = 3;
    m1.columns = 3;
    m1.values = values_1;
    print(&m1);

    Matrix m2;
    m2.rows = 3;
    m2.columns = 3;
    m2.values = values_2;
    print(&m2);

    Matrix m3;
    m3.rows = 3;
    m3.columns = 3;
    m3.values = (float*)malloc(sizeof(float) * m3.rows * m3.columns);

    result = add(&m1, &m2, &m3);
    if (result == 0) {
        fprintf(stdout, "\nAddition result");
        print(&m3);
    } else {
        fprintf(stdout, "\nAddition failed");
    }

    result = subtract(&m1, &m2, &m3);
    if (result == 0) {
        fprintf(stdout, "\nSubtraction result");
        print(&m3);
    } else {
        fprintf(stdout, "\nSubtraction failed");
    }

    result = multiply(&m1, &m2, &m3);
    if (result == 0) {
        fprintf(stdout, "\nMultiplication result");
        print(&m3);
    } else {
        fprintf(stdout, "\nMultiplication failed");
    }
}
