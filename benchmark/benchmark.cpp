/*
 * Serialization-Deserialization Speed Test
 *
 * Source code by Vivatsathorn Thitasirivit
 *
 * You can set network endianness to either network endianness (big endian) or
 * system endianness (usually little endian) or manually by __set_network_endianness(...)
 *
 * The result shows that serialization with conversion is 50% slower than without conversion
 * and deserialization with is 150% slower than without.
 *
 * I recommend you to set the network endianness to the receiver end for faster performance.
 * For microcontroller applications, the little endianness is heavily recommended.
 */

#include "../serializer.h"
#include <time.h>

using namespace vnet;

typedef packed_struct {
    uint16_t a;
    uint32_t b;
    uint16_t c;
    uint32_t d;
} payload_t;

typedef Serializer<payload_t, uint16_t, uint32_t, uint16_t, uint32_t> serializer_t;


int main() {
    clock_t start, stop;
    double elapsed;
    serializer_t ser;
    uint8_t *buf;
    payload_t d;

    __set_network_endianness(VNET_DEFAULT_NETWORK_ENDIANNESS);
    __set_network_endianness(SYSTEM_ENDIANNESS);

    payload_t payload = {0x0e0f, 0x0a0b0c0d, 0xaabb, 0xffffffef};

    start = clock();
    for (int i = 0; i < 10000000; ++i)
        ser = serializer_t();
    stop = clock();
    elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Initialization used %lf s\n", elapsed);

    start = clock();
    for (int i = 0; i < 10000000; ++i)
        buf = ser.serialize(payload);
    stop = clock();
    elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Serialization used %lf s\n", elapsed);

    start = clock();
    for (int i = 0; i < 10000000; ++i)
        d = ser.deserialize(buf);
    stop = clock();
    elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("Deserialization used %lf s\n", elapsed);
    print(d);
}
