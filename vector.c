#include "vector.h"

// creation

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

// methods

inline float* vect_get(Vector* v, int rid) { return v->values + rid; }

void vect_print(Vector* v, char* name) {
    fprintf(stdout, "\n%s :\n", name);
    for (int rid = 0; rid < v->rows; ++rid)
        fprintf(stdout, "| %9.3f |\n", *vect_get(v, rid));
    fprintf(stdout, "\n");
}

// operations

int vect_add(Vector* vin1, Vector* vin2, Vector* vout) {
    // checking rows
    if (vin1->rows != vin2->rows || vin1->rows != vout->rows) return -1;

    for (int rid = 0; rid < vout->rows; ++rid)
        *vect_get(vout, rid) = *vect_get(vin1, rid) + *vect_get(vin2, rid);

    return 0;
}

int vect_sub(Vector* vin1, Vector* vin2, Vector* vout) {
    // checking rows
    if (vin1->rows != vin2->rows || vin1->rows != vout->rows) return -1;

    for (int rid = 0; rid < vout->rows; ++rid)
        *vect_get(vout, rid) = *vect_get(vin1, rid) - *vect_get(vin2, rid);

    return 0;
}

int vect_vect_prod(Vector* vin1, Vector* vin2, float* out) {
    // checking rows
    if (vin1->rows != vin2->rows) return -1;

    *out = 0.0f;
    for (int rid = 0; rid < vin1->rows; ++rid)
        *out += *vect_get(vin1, rid) * *vect_get(vin2, rid);

    return 0;
}
