#include <stdlib.h>
#include "mod.h"
#include "big-uint.h"

void mod_big_uint(uint32_t* result, const uint32_t* n, const uint32_t* p, size_t len) {
    uint32_t quotient[len];

    big_uint_div(quotient, result, n, p, len);
}
