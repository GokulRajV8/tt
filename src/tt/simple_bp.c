#include <stdbool.h>
#include <string.h>

#include "data.h"
#include "functions.h"
#include "idata.h"
#include "ifunctions.h"

/*
Math >>

o1 = w11.i1 + w12.i2 + w13.i3 + b1
o2 = w21.i1 + w22.i2 + w23.i3 + b2
o3 = w31.i1 + w32.i2 + w33.i3 + b3

e = (o1 - oe1) ^ 2 + (o2 - oe2) ^ 2 + (o3 - oe3) ^ 2 / total count

change needed in e = -1 * (  max_change_in_error_squared < e
                           ? max_change_in_error_squared
                           : e)

de / dx = change needed in e / change needed in x
change needed in x = change needed in e / (de / dx)

de / dx =   2 * (o1 - oe1) * do1/dx
          + 2 * (o2 - oe2) * do2/dx
          + 2 * (o3 - oe3) * do3/dx

de / dw11 = 2 * (o1 - oe1) * i1
de / di1  = 2 * (o1 - oe1) * w11 + 2 * (o2 - oe2) * w21 + 2 * (o3 - oe3) * w31
de / db1  = 2 * (o1 - oe1) * 1

delta = 2 * (o1 - oe1)
*/

static void update_value_with_bounds(float* val, float change, bool is_bias) {
    *val += change;
    if (*val > 1.0f) *val = 1.0f;
    if (is_bias) {
        if (*val < -1.0f) *val = -1.0f;
    } else {
        if (*val < 0.0f) *val = 0.0f;
    }
}

int tt_sbp_error_propagate(struct TTBlock* b, struct TTVector* vin,
                           struct TTVector* vexp,
                           float max_change_in_error_squared) {
    // checking expected vector size
    if (tt_block_get_out_size(b) != vexp->rows) return -1;

    struct TTVector vout = tt_vector_init(tt_block_get_out_size(b));
    struct GranularLayerInput gli_for_transform =
        block_transform_granular(b, vin, &vout);
    if (!gli_for_transform.was_successful) {
        tt_vector_delete(&vout);
        return -1;
    }

    // back propagation
    for (unsigned int layer_id = b->layers_count - 1;; --layer_id) {
        // current weights, bias, input vector and expected output vector
        struct TTMatrix* curr_weights = &b->layers[layer_id].weights;
        struct TTVector* curr_bias = &b->layers[layer_id].bias;
        struct TTVector* curr_vin = gli_for_transform.inputs + layer_id;
        struct TTVector* curr_vexp =
            (layer_id == b->layers_count - 1) ? vexp : curr_vin + 1;

        // delta vector
        struct TTVector delta_vector = tt_vector_init(curr_vexp->rows);
        for (unsigned int rid = 0; rid < delta_vector.rows; ++rid)
            *tt_vector_get_data(&delta_vector, rid) =
                2 * (*tt_vector_get_data(&vout, rid) -
                     *tt_vector_get_data(curr_vexp, rid));

        // mean square error and change needed
        float e = 0.0f;
        for (unsigned int rid = 0; rid < delta_vector.rows; ++rid)
            e += 0.25 * (*tt_vector_get_data(&delta_vector, rid) *
                         *tt_vector_get_data(&delta_vector, rid));
        e /= delta_vector.rows;
        float de = -1 * ((max_change_in_error_squared < e)
                             ? max_change_in_error_squared
                             : e);

        // change needed in weights - dw
        struct TTMatrix dw_matrix =
            matrix_init(curr_vexp->rows, curr_vin->rows);
        for (unsigned int rid = 0; rid < curr_vexp->rows; ++rid) {
            for (unsigned int cid = 0; cid < curr_vin->rows; ++cid) {
                float de_by_di = (*tt_vector_get_data(&delta_vector, rid) *
                                  *tt_vector_get_data(curr_vin, cid));
                if (de_by_di != 0)
                    *matrix_get_data(&dw_matrix, rid, cid) = de / de_by_di;
                else
                    *matrix_get_data(&dw_matrix, rid, cid) = 0;
            }
        }

        // change needed in bias - db
        struct TTVector db_vector = tt_vector_init(curr_vexp->rows);
        for (unsigned int rid = 0; rid < curr_vexp->rows; ++rid) {
            if (*tt_vector_get_data(&delta_vector, rid) != 0)
                *tt_vector_get_data(&db_vector, rid) =
                    de / *tt_vector_get_data(&delta_vector, rid);
            else
                *tt_vector_get_data(&db_vector, rid) = 0;
        }

        // change needed in inputs - di
        struct TTVector di_vector = tt_vector_init(curr_vin->rows);
        for (unsigned int cid = 0; cid < curr_vin->rows; ++cid) {
            float de_by_di = 0.0f;
            for (unsigned int rid = 0; rid < curr_vexp->rows; ++rid) {
                de_by_di += *tt_vector_get_data(&delta_vector, rid) *
                            *matrix_get_data(curr_weights, rid, cid);
            }
            if (de_by_di != 0)
                *tt_vector_get_data(&di_vector, cid) = de / de_by_di;
            else
                *tt_vector_get_data(&di_vector, cid) = 0;
        }

        // copying current input vector into output vector
        vector_resize(&vout, curr_vin->rows);
        memcpy(vout.data, curr_vin->data, sizeof(float) * curr_vin->rows);

        // updating values of current layer
        for (unsigned int rid = 0; rid < curr_vexp->rows; ++rid) {
            for (unsigned int cid = 0; cid < curr_vin->rows; ++cid)
                update_value_with_bounds(
                    matrix_get_data(curr_weights, rid, cid),
                    *matrix_get_data(&dw_matrix, rid, cid), false);
            update_value_with_bounds(tt_vector_get_data(curr_bias, rid),
                                     *tt_vector_get_data(&db_vector, rid),
                                     true);
        }
        for (unsigned int cid = 0; cid < curr_vin->rows; ++cid)
            update_value_with_bounds(tt_vector_get_data(curr_vin, cid),
                                     *tt_vector_get_data(&di_vector, cid),
                                     false);

        // deleting change needed vectors
        tt_vector_delete(&di_vector);
        tt_vector_delete(&db_vector);
        matrix_delete(&dw_matrix);
        tt_vector_delete(&delta_vector);

        // breaking here as unsigned int does not support -1
        if (layer_id == 0) break;
    }

    vector_list_delete(b->layers_count, gli_for_transform.inputs);
    tt_vector_delete(&vout);
    return 0;
}
