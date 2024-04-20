#include "vector_transform_layer.h"

// creation and deletion

struct VectorTransformLayer vtl_init(uint32_t in_size, uint32_t out_size,
                                     float* data) {
    struct VectorTransformLayer vtl;
    vtl.in_size = in_size;
    vtl.out_size = out_size;

    // creating matrix and vector
    vtl.weights = matx_init_data(out_size, in_size, data);
    vtl.bias = vect_init_data(out_size, data + (out_size * in_size));

    return vtl;
}

void vtl_delete(struct VectorTransformLayer* vtl) {
    matx_delete(&vtl->weights);
    vect_delete(&vtl->bias);
}

// operations

int vtl_transform(struct VectorTransformLayer* vtl, struct Vector* vin,
                  struct Vector* vout) {
    // checking input and output dimensions
    if (vin->rows != vtl->in_size || vout->rows != vtl->out_size) return -1;

    struct Vector intermediate = vect_init_bare(vtl->out_size);
    matx_vect_prod(&vtl->weights, vin, &intermediate);
    vect_add(&intermediate, &vtl->bias, vout);
    vect_delete(&intermediate);

    return 0;
}
