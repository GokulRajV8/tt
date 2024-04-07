#include "matrix.h"

int add(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking rows
    if (min1->rows != min2->rows || min1->rows != mout->rows) return -1;

    // checking columns
    if (min1->columns != min2->columns || min1->columns != mout->columns)
        return -1;

    for (int row_id = 0; row_id < mout->rows; ++row_id) {
        for (int column_id = 0; column_id < mout->columns; ++column_id)
            *(mout->values + mout->columns * row_id + column_id) =
                *(min1->values + min1->columns * row_id + column_id) +
                *(min2->values + min2->columns * row_id + column_id);
    }

    return 0;
}

int subtract(Matrix* min1, Matrix* min2, Matrix* mout) {
    // checking rows
    if (min1->rows != min2->rows || min1->rows != mout->rows) return -1;

    // checking columns
    if (min1->columns != min2->columns || min1->columns != mout->columns)
        return -1;

    for (int row_id = 0; row_id < mout->rows; ++row_id) {
        for (int column_id = 0; column_id < mout->columns; ++column_id)
            *(mout->values + mout->columns * row_id + column_id) =
                *(min1->values + min1->columns * row_id + column_id) -
                *(min2->values + min2->columns * row_id + column_id);
    }

    return 0;
}

int multiply(Matrix* min1, Matrix* min2, Matrix* mout) {
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
