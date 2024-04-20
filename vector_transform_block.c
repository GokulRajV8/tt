#include "vector_transform_block.h"

// creation and deletion

struct VectorTransformBlock vtb_init(uint32_t layers_count,
                                     uint32_t* layer_input_size,
                                     uint32_t output_size, float** values) {
    struct VectorTransformBlock vtb;

    vtb.layers_count = layers_count;
    vtb.layers = (struct VectorTransformLayer*)malloc(
        sizeof(struct VectorTransformLayer) * vtb.layers_count);

    for (uint32_t layer_id = 0; layer_id < vtb.layers_count; ++layer_id)
        *(vtb.layers + layer_id) =
            vtl_init(*(layer_input_size + layer_id),
                     layer_id != vtb.layers_count - 1
                         ? *(layer_input_size + layer_id + 1)
                         : output_size,
                     *(values + layer_id));

    return vtb;
}

void vtb_delete(struct VectorTransformBlock* vtb) {
    for (uint32_t layer_id = 0; layer_id < vtb->layers_count; ++layer_id)
        vtl_delete(vtb->layers + layer_id);
    free(vtb->layers);
}

// operations

int vtb_transform(struct VectorTransformBlock* vtb, struct Vector* vin,
                  struct Vector* vout) {
    // checking input and output dimensions
    if ((vtb->layers)->in_size != vin->rows ||
        (vtb->layers + (vtb->layers_count - 1))->out_size != vout->rows)
        return -1;

    struct Vector v_temp = vect_init_bare(vin->rows);
    vect_copy(vin, &v_temp);
    for (uint32_t layer_id = 0; layer_id < vtb->layers_count; ++layer_id) {
        vect_resize(vout, (vtb->layers + layer_id)->out_size);
        vtl_transform((vtb->layers + layer_id), &v_temp, vout);
        vect_copy(vout, &v_temp);
    }
    vect_delete(&v_temp);

    return 0;
}
