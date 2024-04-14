#include "matrix.h"

// creation

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

// methods

inline float* matx_get(Matrix* m, int rid, int cid) {
    return (m->values + (rid * m->columns) + cid);
}

void matx_print(Matrix* m, char* name) {
    fprintf(stdout, "\n%s :\n", name);
    for (int rid = 0; rid < m->rows; ++rid) {
        fprintf(stdout, "|");
        for (int cid = 0; cid < m->columns; ++cid)
            fprintf(stdout, " %9.3f", *matx_get(m, rid, cid));
        fprintf(stdout, " |\n");
    }
    fprintf(stdout, "\n");
}

// operations

int matx_add(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking rows
    if (min1->rows != min2->rows || min1->rows != mout->rows) return -1;

    // checking columns
    if (min1->columns != min2->columns || min1->columns != mout->columns)
        return -1;

    for (int rid = 0; rid < mout->rows; ++rid)
        for (int cid = 0; cid < mout->columns; ++cid)
            *matx_get(mout, rid, cid) =
                *matx_get(min1, rid, cid) + *matx_get(min2, rid, cid);

    return 0;
}

int matx_sub(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking rows
    if (min1->rows != min2->rows || min1->rows != mout->rows) return -1;

    // checking columns
    if (min1->columns != min2->columns || min1->columns != mout->columns)
        return -1;

    for (int rid = 0; rid < mout->rows; ++rid)
        for (int cid = 0; cid < mout->columns; ++cid)
            *matx_get(mout, rid, cid) =
                *matx_get(min1, rid, cid) - *matx_get(min2, rid, cid);

    return 0;
}

int matx_vect_prod(Matrix* min, Vector* vin, Vector* vout) {
    // checking dimensions
    if (min->columns != vin->rows || min->rows != vout->rows) return -1;

    float val;
    for (int rid = 0; rid < min->rows; ++rid) {
        val = 0.0f;
        for (int i = 0; i < min->columns; ++i)
            val += *matx_get(min, rid, i) * *vect_get(vin, i);
        *vect_get(vout, rid) = val;
    }

    return 0;
}

int matx_matx_prod(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking input dimensions
    if (min1->columns != min2->rows) return -1;

    // checking output dimensions
    if (min1->rows != mout->rows || min2->columns != mout->columns) return -1;

    for (int in1_rid = 0; in1_rid < min1->rows; ++in1_rid)
        for (int in2_cid = 0; in2_cid < min2->columns; ++in2_cid) {
            float val = 0;
            for (int i = 0; i < min1->columns; ++i)
                val +=
                    *matx_get(min1, in1_rid, i) * *matx_get(min2, i, in2_cid);
            *matx_get(mout, in1_rid, in2_cid) = val;
        }

    return 0;
}
