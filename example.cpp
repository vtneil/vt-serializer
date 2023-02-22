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
     * Setting the endianness of the network.
     * Available parameters:
     * Default: VNET_DEFAULT_NETWORK_ENDIANNESS (Little endian)
     * Network: NETWORK_ENDIANNESS
     * Machine: SYSTEM_ENDIANNESS
     * Manually: vnet::SYS_BIG_ENDIAN or vnet::SYS_LITTLE_ENDIAN
     */
    __set_network_endianness(vnet::SYS_BIG_ENDIAN);

    /*
     * Initialize/construct payload and serializer
     */
    payload_t payload = {23, 150, 1023, 13.000111, 100.445678};
    serializer_t serializer = serializer_t();

    /*
     * Serialize (1)
     * Make a temporary byte buffer and
     * serialize the payload using "serialize(...)"
     */
    uint8_t *buf1 = serializer.serialize(payload);

    /*
     * Serialize (2)
     * Make a temporary buffer and
     * serialize the payload using "serialize_to(...)"
     */
    uint8_t *buf2 = (uint8_t *) malloc(serializer.buffer_size());
    serializer.serialize_to(buf2, payload);

    /*
     * Try printing the byte order (or send data to network)
     */
    printf("Sender Device (Serialized bytes)\n");
    printb(buf1, serializer.buffer_size());
    hrb();

    /*
     * In case that receiver device already read the whole buffer
     * Use deserialize(...) or deserialize_to(...)
     */
    payload_t read_payload = serializer.deserialize(buf2);

    printf("Receiver Device (Deserialized bytes, the same as original struct)\n");
    printb(read_payload);
    hr();
    printf("translates to:\n");

    printf("field 1: %d\n", read_payload.payload_id);
    printf("field 2: %d\n", read_payload.packet);
    printf("field 3: %d\n", read_payload.pressure);
    printf("field 4: %f\n", read_payload.latitude);
    printf("field 5: %f\n", read_payload.longitude);
    hrd();
    printf("Comparing data to CSV string\n");
    printf("CSV    takes %d bytes.\n",
           snprintf(nullptr, 0,
                    "%d,%d,%d,%f,%f,", read_payload.payload_id, read_payload.packet, read_payload.pressure,
                    read_payload.latitude, read_payload.longitude
           )
    );
    printf("Struct takes %ld bytes (constant).\n", serializer.buffer_size());


    return 0;
}