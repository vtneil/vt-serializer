/*
 * C++ Struct Serializer-Deserializer
 * Example: How to construct a Serializer-Deserializer
 *
 * Source code by Vivatsathorn Thitasirivit
 */

/*
 * Include serializer.h in your directory
 */
#include "serializer.h"

/*
 * Set namespace vnet
 */
using namespace vnet;

/*
 * Make a struct using macro "packed_struct", which you can use like a normal struct.
 * Macro "typedef_packed_struct" is also included for convenience; it just acts like
 * when you type "typedef packed_struct".
 */
typedef_packed_struct {
    uint8_t payload_id;
    uint32_t packet;
    uint32_t pressure;
    float latitude;
    float longitude;
} payload_t;

/*
 * Typedef the serializer for ease of usages.
 *
 * Then using the serializer, add these to the template like the example.
 * 1. First field: typename of the struct
 * 2. Remaining field: sorted typename(s) of struct members
 * 3. If you are sure that network endianness is the same, you can omit 2.
 *    (not needing conversion)
 */
typedef Serializer<payload_t, uint8_t, uint32_t, uint32_t, float, float> serializer_t;


int main() {
    /*
     * Initialize/construct payload and serializer
     */
    payload_t payload = {23, 150, 1023, 13.000111, 100.445678};
    serializer_t serializer = serializer_t();

    return 0;
}