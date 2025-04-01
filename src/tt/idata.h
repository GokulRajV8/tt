// Contains all the data structures used internally by TT library

#ifndef TT_IDATA_H
#define TT_IDATA_H

#include <stdbool.h>

#include "data.h"

struct GranularLayerInput {
    bool was_successful;
    struct TTVector* inputs;
};

#endif
