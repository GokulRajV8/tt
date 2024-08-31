#include "vector.h"

// creation and deletion

struct Vector vect_init_bare(uint32_t rows) {
    struct Vector v;
    v.rows = rows;
    v.values = malloc(sizeof(float) * v.rows);

    return v;
}

struct Vector vect_init_data(uint32_t rows, float* data) {
    struct Vector v = vect_init_bare(rows);
    memcpy(v.values, data, sizeof(float) * v.rows);

    return v;
}

void vect_delete(struct Vector* v) { free(v->values); }

// methods

float* vect_get(struct Vector* v, uint32_t rid) { return v->values + rid; }

void vect_resize(struct Vector* v, uint32_t rows) {
    v->rows = rows;
    v->values = realloc(v->values, sizeof(float) * v->rows);
}

void vect_copy(struct Vector* vsrc, struct Vector* vdest) {
    vect_resize(vdest, vsrc->rows);
    memcpy(vdest->values, vsrc->values, sizeof(float) * vsrc->rows);
}

void vect_print(struct Vector* v, char* name) {
    fprintf(stdout, "\n%s :\n", name);
    for (uint32_t rid = 0; rid < v->rows; ++rid)
        fprintf(stdout, "| %9.6f |\n", *vect_get(v, rid));
    fprintf(stdout, "\n");
}

// operations

int vect_add(struct Vector* vin1, struct Vector* vin2, struct Vector* vout) {
    // checking rows
    if (vin1->rows != vin2->rows || vin1->rows != vout->rows) return -1;

    for (uint32_t rid = 0; rid < vout->rows; ++rid)
        *vect_get(vout, rid) = *vect_get(vin1, rid) + *vect_get(vin2, rid);

    return 0;
}

int vect_sub(struct Vector* vin1, struct Vector* vin2, struct Vector* vout) {
    // checking rows
    if (vin1->rows != vin2->rows || vin1->rows != vout->rows) return -1;

    for (uint32_t rid = 0; rid < vout->rows; ++rid)
        *vect_get(vout, rid) = *vect_get(vin1, rid) - *vect_get(vin2, rid);

    return 0;
}

int vect_vect_prod(struct Vector* vin1, struct Vector* vin2, float* out) {
    // checking rows
    if (vin1->rows != vin2->rows) return -1;

    *out = 0.0f;
    for (uint32_t rid = 0; rid < vin1->rows; ++rid)
        *out += *vect_get(vin1, rid) * *vect_get(vin2, rid);

    return 0;
}
