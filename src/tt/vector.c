#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "functions.h"
#include "ifunctions.h"

struct TTVector tt_vector_init(unsigned int rows) {
    struct TTVector v;
    v.rows = rows;
    v.data = malloc(sizeof(float) * rows);

    return v;
}

void tt_vector_delete(struct TTVector* v) {
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
    }
}

float* tt_vector_get_data(struct TTVector* v, unsigned int rid) {
    return v->data + rid;
}

struct TTVector* vector_list_init(unsigned int count, unsigned int* sizes) {
    struct TTVector* vlist = malloc(sizeof(struct TTVector) * count);
    for (unsigned int i = 0; i < count; ++i) {
        vlist[i].rows = sizes[i];
        vlist[i].data = malloc(sizeof(float) * sizes[i]);
    }

    return vlist;
}

void vector_list_delete(unsigned int count, struct TTVector* vlist) {
    for (unsigned int i = 0; i < count; ++i) tt_vector_delete(vlist + i);
    free(vlist);
}

void vector_resize(struct TTVector* v, unsigned int rows) {
    v->rows = rows;
    v->data = realloc(v->data, sizeof(float) * rows);
}

void vector_add(struct TTVector* vin1, struct TTVector* vin2,
                struct TTVector* vout) {
    for (unsigned int rid = 0; rid < vin1->rows; rid++)
        *tt_vector_get_data(vout, rid) =
            *tt_vector_get_data(vin1, rid) + *tt_vector_get_data(vin2, rid);
}

void vector_print(struct TTVector* v, char* name) {
    fprintf(stdout, "%s :\n", name);
    for (unsigned int rid = 0; rid < v->rows; ++rid) {
        fprintf(stdout, "%f\n", *tt_vector_get_data(v, rid));
    }
    fprintf(stdout, "\n");
}
