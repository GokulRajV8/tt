#include "data.h"
#include "functions.h"
#include "ifunctions.h"

float* tt_layer_get_weight(struct TTLayer* l, unsigned int rid,
                           unsigned int cid) {
    return matrix_get_data(&l->weights, rid, cid);
}

float* tt_layer_get_bias(struct TTLayer* l, unsigned int rid) {
    return tt_vector_get_data(&l->bias, rid);
}

void layer_transform(struct TTLayer* l, struct TTVector* vin,
                     struct TTVector* vout) {
    struct TTVector prod_result = tt_vector_init(l->out_size);

    matrix_vector_prod(&l->weights, vin, &prod_result);
    vector_add(&prod_result, &l->bias, vout);

    // bounds check
    for (unsigned int rid = 0; rid < vout->rows; ++rid) {
        if (*tt_vector_get_data(vout, rid) > 1.0f)
            *tt_vector_get_data(vout, rid) = 1.0f;
        else if (*tt_vector_get_data(vout, rid) < -1.0f)
            *tt_vector_get_data(vout, rid) = -1.0f;
    }

    tt_vector_delete(&prod_result);
}
