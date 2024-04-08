#include "matrix.h"

Matrix matx_init_bare(int rows, int columns) {
    Matrix m;
    m.rows = rows;
    m.columns = columns;
    m.values = (float*)malloc(sizeof(float) * m.rows * m.columns);

    return m;
}

Matrix matx_init_data(int rows, int columns, float* data) {
    Matrix m = matx_init_bare(rows, columns);
    memcpy(m.values, data, sizeof(float) * m.rows * m.columns);

    return m;
}

int matx_add(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking rows
    if (min1->rows != min2->rows || min1->rows != mout->rows) return -1;

    // checking columns
    if (min1->columns != min2->columns || min1->columns != mout->columns)
        return -1;

    for (int rid = 0; rid < mout->rows; ++rid) {
        for (int cid = 0; cid < mout->columns; ++cid)
            *(mout->values + mout->columns * rid + cid) =
                *(min1->values + min1->columns * rid + cid) +
                *(min2->values + min2->columns * rid + cid);
    }

    return 0;
}

int matx_sub(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking rows
    if (min1->rows != min2->rows || min1->rows != mout->rows) return -1;

    // checking columns
    if (min1->columns != min2->columns || min1->columns != mout->columns)
        return -1;

    for (int rid = 0; rid < mout->rows; ++rid) {
        for (int cid = 0; cid < mout->columns; ++cid)
            *(mout->values + mout->columns * rid + cid) =
                *(min1->values + min1->columns * rid + cid) -
                *(min2->values + min2->columns * rid + cid);
    }

    return 0;
}

int matx_vect_prod(Matrix* min, Vector* vin, Vector* vout) {
    // checking dimensions
    if (min->columns != vin->rows || min->rows != vout->rows) return -1;

    float val;
    for (int rid = 0; rid < min->rows; ++rid) {
        val = 0.0f;
        for (int i = 0; i < min->columns; ++i)
            val += *(min->values + min->columns * rid + i) * *(vin->values + i);
        *(vout->values + rid) = val;
    }

    return 0;
}

int matx_matx_prod(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking input dimensions
    if (min1->columns != min2->rows) return -1;

    // checking output dimensions
    if (min1->rows != mout->rows || min2->columns != mout->columns) return -1;

    for (int in1_rid = 0; in1_rid < min1->rows; ++in1_rid) {
        for (int in2_cid = 0; in2_cid < min2->columns; ++in2_cid) {
            float val = 0;
            for (int i = 0; i < min1->columns; ++i) {
                val += *(min1->values + min1->columns * in1_rid + i) *
                       *(min2->values + min2->columns * i + in2_cid);
            }
            *(mout->values + mout->columns * in1_rid + in2_cid) = val;
        }
    }

    return 0;
}

void matx_print(Matrix* m) {
    fprintf(stdout, "\nRows : %d", m->rows);
    fprintf(stdout, "\nColumns : %d", m->columns);

    fprintf(stdout, "\nValues ->\n");
    for (int rid = 0; rid < m->rows; ++rid) {
        fprintf(stdout, "|");
        for (int column_id = 0; column_id < m->columns; ++column_id)
            fprintf(stdout, "%3.2f ",
                    *(m->values + (rid * m->columns) + column_id));
        fprintf(stdout, "|\n");
    }
    fprintf(stdout, "\n");
}
