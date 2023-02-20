#include "serializer.h"

typedef struct {
    uint16_t a;
    uint16_t b;
    uint8_t c;
    uint32_t d;
} t1;

typedef struct {
    long double a;
} t2;

typedef vnet::Payload<t1> p1;
typedef vnet::Payload<t2> p2;

int main() {
    vnet::set_network_endianness(VNET_DEFAULT_NETWORK_ENDIANNESS);

    t1 sender{0x14, 0x66, 0x78, 0xdf};
    t2 control{25.968734};

    // Don't forget to free this memory later!
    uint8_t *serialized = p1::serialize(sender);

    t1 receiver{};

    printf("Example 1: basic\n");
    // Machine data representation
    vnet::print(sender);
    vnet::hr(p1::size() * 3 + 7);

    // Network data representation
    vnet::print(serialized, p1::size());
    vnet::hrd(p1::size() * 3 + 7);

    // Using deserialize to buffer dst
    p1::deserialize_to(receiver, serialized);

    // Network deserialized to Machine data
    vnet::print(receiver);
    vnet::hr(p1::size() * 3 + 7);

    // Can also use deserialize without buffer (return value instead)
    vnet::print(p1::deserialize(serialized));

    vnet::hrt(p1::size() * 3 + 7);

    // Another examples
    printf("Example 2: double\n");
    vnet::print(control);
    vnet::hrt(p2::size() * 3 + 7);
    vnet::print(p2::serialize(control), p2::size());

    // Again, don't forget to free the serialized data (uint8_t[] aka char[]).
    free(serialized);
}
