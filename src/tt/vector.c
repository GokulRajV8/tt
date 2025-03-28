#include <stdlib.h>

#include "data.h"
#include "functions.h"
#include "ifunctions.h"

struct TTVector tt_vector_init(unsigned int rows) {
    struct TTVector v;
    v.rows = rows;
    v.data = malloc(rows * sizeof(float));

    return v;
}

void tt_vector_delete(struct TTVector* v) { free(v->data); }

float* tt_vector_get_data(struct TTVector* v, unsigned int rid) {
    return v->data + rid;
}

void vector_resize(struct TTVector* v, unsigned int rows) {
    v->rows = rows;
    v->data = realloc(v->data, rows * sizeof(float));
}

void vector_add(struct TTVector* vin1, struct TTVector* vin2,
                struct TTVector* vout) {
    for (unsigned int rid = 0; rid < vin1->rows; rid++)
        *tt_vector_get_data(vout, rid) =
            *tt_vector_get_data(vin1, rid) + *tt_vector_get_data(vin2, rid);
}
