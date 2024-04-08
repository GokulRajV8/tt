#include "vector.h"

Vector vect_init_bare(int rows) {
    Vector v;
    v.rows = rows;
    v.values = (float*)malloc(sizeof(float) * v.rows);

    return v;
}

Vector vect_init_data(int rows, float* data) {
    Vector v = vect_init_bare(rows);
    memcpy(v.values, data, sizeof(float) * v.rows);

    return v;
}

int vect_add(Vector* vin1, Vector* vin2, Vector* vout) {
    // checking rows
    if (vin1->rows != vin2->rows || vin1->rows != vout->rows) return -1;

    for (int rid = 0; rid < vout->rows; ++rid)
        *(vout->values + rid) = *(vin1->values + rid) + *(vin2->values + rid);

    return 0;
}

int vect_sub(Vector* vin1, Vector* vin2, Vector* vout) {
    // checking rows
    if (vin1->rows != vin2->rows || vin1->rows != vout->rows) return -1;

    for (int rid = 0; rid < vout->rows; ++rid)
        *(vout->values + rid) = *(vin1->values + rid) - *(vin2->values + rid);

    return 0;
}

int vect_vect_prod(Vector* vin1, Vector* vin2, float* out) {
    // checking rows
    if (vin1->rows != vin2->rows) return -1;

    *out = 0.0f;
    for (int rid = 0; rid < vin1->rows; ++rid)
        *out += *(vin1->values + rid) * *(vin2->values + rid);

    return 0;
}

int vect_matx_prod(Matrix* min, Vector* vin, Vector* vout) {
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

void vect_print(Vector* v) {
    fprintf(stdout, "\nRows : %d", v->rows);

    fprintf(stdout, "\nValues ->\n");
    for (int rid = 0; rid < v->rows; ++rid)
        fprintf(stdout, "| %3.2f |\n", *(v->values + rid));
    fprintf(stdout, "\n");
}
