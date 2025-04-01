#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "functions.h"
#include "ifunctions.h"

struct TTMatrix matrix_init(unsigned int rows, unsigned int cols) {
    struct TTMatrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = malloc(sizeof(float) * m.rows * m.cols);

    return m;
}

void matrix_delete(struct TTMatrix* m) {
    if (m->data != NULL) {
        free(m->data);
        m->data = NULL;
    }
}

float* matrix_get_data(struct TTMatrix* m, unsigned int rid, unsigned int cid) {
    return m->data + rid * m->cols + cid;
}

void matrix_vector_prod(struct TTMatrix* min, struct TTVector* vin,
                        struct TTVector* vout) {
    float val;
    for (unsigned int rid = 0; rid < min->rows; ++rid) {
        val = 0.0f;
        for (unsigned int cid = 0; cid < min->cols; ++cid)
            val +=
                *matrix_get_data(min, rid, cid) * *tt_vector_get_data(vin, cid);
        *tt_vector_get_data(vout, rid) = val;
    }
}

void matrix_print(struct TTMatrix* m, char* name) {
    fprintf(stdout, "%s :\n", name);
    for (unsigned int rid = 0; rid < m->rows; ++rid) {
        for (unsigned int cid = 0; cid < m->cols; ++cid)
            fprintf(stdout, "%f ", *matrix_get_data(m, rid, cid));
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}
