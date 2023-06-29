#ifndef VT_SERIALIZER_SERIALIZER_H
#define VT_SERIALIZER_SERIALIZER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "serializer_utility.h"
#include "memory_buffer.h"

namespace vt {
    enum Endianness {
        SYS_BIG_ENDIAN = 0,
        SYS_LITTLE_ENDIAN,
        UNSPECIFIED
    };

    enum Endianness get_sys_endianness() {
        uint16_t word = 0x01;
        uint8_t *byte_arr = reinterpret_cast<uint8_t *>(&word);
        return *byte_arr ? SYS_LITTLE_ENDIAN : SYS_BIG_ENDIAN;
    }

    static enum Endianness SYSTEM_ENDIANNESS = get_sys_endianness();
    static enum Endianness NETWORK_ENDIANNESS = UNSPECIFIED;

    template<typename S>
    class serializer {
    public:
        serializer() = delete;

        serializer(const serializer &) = delete;

        serializer(serializer &&) noexcept = delete;

        serializer &operator=(const serializer &) = delete;

        serializer &operator=(serializer &&) = delete;

        /**
         * Serialize struct data into memory buffer.
         *
         * @param data
         * @return
         */
        static memory_buffer<S> serialize(const S &data) {
            memory_buffer<S> return_data(data);
            return return_data;
        }

        /**
         * Deserialize into struct data from memory buffer.
         *
         * @param data
         * @return
         */
        static S deserialize(const memory_buffer<S> &data) {
            S return_data;
            memcpy(&return_data, data.ptr(), sizeof(S));
            return return_data;
        }

        /**
         * Deserialize into struct data from byte pool.
         *
         * @param data
         * @return
         */
        static S deserialize(const byte_pool &data) {
            S return_data;
            memcpy(&return_data, data.ptr(), sizeof(S));
            return return_data;
        }

        /**
         * Deserialize into struct data from byte pointer.
         *
         * @param data
         * @return
         */
        static S deserialize(void *data) {
            S return_data;
            memcpy(reinterpret_cast<uint8_t *>(&return_data), reinterpret_cast<uint8_t *>(data), sizeof(S));
            return return_data;
        }
    };
}

#endif //VT_SERIALIZER_SERIALIZER_H
