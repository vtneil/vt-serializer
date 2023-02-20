#ifndef NETWORK_SERIALIZER_H
#define NETWORK_SERIALIZER_H

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>

#define VNET_DEFAULT_NETWORK_ENDIANNESS vnet::SYS_BIG_ENDIAN

namespace vnet {
    typedef enum {
        SYS_BIG_ENDIAN = 0,
        SYS_LITTLE_ENDIAN
    } Endianness;

    Endianness get_sys_endianness();

    template<typename T>
    T reverse_bits(T data);

    template<typename T>
    void print(const T &data, size_t size = sizeof(T));

    template<typename T>
    void print(T *data, size_t size);

    static Endianness SYSTEM_ENDIANNESS = get_sys_endianness();
    static Endianness NETWORK_ENDIANNESS = SYS_BIG_ENDIAN;

    static void set_network_endianness(Endianness endianness) {
        NETWORK_ENDIANNESS = endianness;
    }

    template<typename struct_t>
    class Payload {
    public:
        static void serialize_to(uint8_t *dst, const struct_t &src) {
            if (SYSTEM_ENDIANNESS == NETWORK_ENDIANNESS) {
                memcpy(dst, &src, size());
            } else {
                struct_t reversed = reverse_bits(src);
                memcpy(dst, &reversed, size());
            }
        }

        static uint8_t *serialize(const struct_t &src) {
            uint8_t *tmp = (uint8_t *) malloc(size());
            serialize_to(tmp, src);
            return tmp;
        }

        static void deserialize_to(struct_t &dst, uint8_t *src, size_t n = sizeof(struct_t)) {
            if (SYSTEM_ENDIANNESS == NETWORK_ENDIANNESS) {
                memcpy(&dst, src, n);
            } else {
                struct_t tmp = reverse_bits(*((struct_t *) src));
                memcpy(&dst, &tmp, n);
            }
        }

        static struct_t deserialize(uint8_t *src) {
            struct_t tmp;
            deserialize_to(tmp, src);
            return tmp;
        }

        static constexpr size_t size() {
            return sizeof(struct_t);
        }
    };

    Endianness get_sys_endianness() {
        uint16_t word = 0x01;
        auto *byte_arr = (uint8_t *) &word;
        return *byte_arr ? SYS_LITTLE_ENDIAN : SYS_BIG_ENDIAN;
    }

    template<typename T>
    T reverse_bits(T data) {
        T result = {0};
        size_t n = sizeof(T) / sizeof(uint8_t);
        uint8_t *c_data = (uint8_t *) &data;
        uint8_t *tmp = (uint8_t *) &result;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 8 * sizeof(uint8_t); ++j) {
                *(tmp + n - i - 1) <<= 1;
                *(tmp + n - i - 1) |= *(c_data + i) & 1;
                *(c_data + i) >>= 1;
            }
        }

        return *((T *) tmp);
    }

    template<typename T>
    void print(const T &data, size_t size) {
        uint8_t *data_r = (uint8_t *) &data;
        printf("DATA | ");
        for (size_t i = 0; i < size; ++i)
            printf("%02x ", data_r[i]);
        if (SYSTEM_ENDIANNESS) printf("(MSB)");
        else printf("(LSB)");
        printf("\n");
        printf("ADDR | ");
        for (size_t i = 0; i < size; ++i)
            printf("%02lx ", i);
        printf("(HIGH ADDR)\n");
    }

    template<typename T>
    void print(T *data, size_t size) {
        uint8_t *data_r = (uint8_t *) data;
        printf("DATA | ");
        for (size_t i = 0; i < size; ++i)
            printf("%02x ", data_r[i]);
        if (SYSTEM_ENDIANNESS) printf("(MSB)");
        else printf("(LSB)");
        printf("\n");
        printf("ADDR | ");
        for (size_t i = 0; i < size; ++i)
            printf("%02lx ", i);
        printf("(HIGH ADDR)\n");
    }

    void hr(size_t n) {
        while (--n)
            printf("-");
        printf("\n");
    }

    void hrd(size_t n) {
        while (--n)
            printf("=");
        printf("\n");
    }

    void hrt(size_t n) {
        while (--n)
            printf("~");
        printf("\n");
    }
}

#endif //NETWORK_SERIALIZER_H
