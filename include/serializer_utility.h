#ifndef VT_SERIALIZER_SERIALIZER_UTILITY_H
#define VT_SERIALIZER_SERIALIZER_UTILITY_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef packed_struct
#undef packed_struct
#endif
#define packed_struct struct __attribute__((packed))

namespace vt {
    void rmemcpy(void *dst, const void *src, size_t n) {
        uint8_t *c_dst = static_cast<uint8_t *>(dst);
        const uint8_t *c_src = static_cast<const uint8_t *>(src) + n - 1;
        while (n--) *c_dst++ = *c_src--;
    }

    template<typename S>
    S reverse_bit_order(S data) {
        S result = {0};
        size_t n = sizeof(S) / sizeof(uint8_t);
        uint8_t *c_data = (uint8_t *) &data;
        uint8_t *tmp = (uint8_t *) &result;

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < 8 * sizeof(uint8_t); ++j) {
                *(tmp + n - i - 1) <<= 1;
                *(tmp + n - i - 1) |= *(c_data + i) & 1;
                *(c_data + i) >>= 1;
            }
        }

        return *((S *) tmp);
    }
}

#endif //VT_SERIALIZER_SERIALIZER_UTILITY_H
