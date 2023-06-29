#include <iostream>
#include "vt_serializer"

using namespace vt;


typedef packed_struct {
    uint8_t u8_data;
    uint16_t u16_data;
    uint32_t u32_data;
    uint64_t u64_data;
    float fp_data;
    double dp_data;
} data_s;


int main() {
    memory_buffer<int> m1(5);
    int x = *m1;
    memory_buffer<int> m2(x);

    data_s data = {
            249,
            64321,
            UINT32_MAX,
            UINT64_MAX,
            159.998,
            1.1299
    };

    std::cout << sizeof(data_s) << "\n\n";

    std::cout << data.u8_data << '\n';
    std::cout << data.u16_data << '\n';
    std::cout << data.u32_data << '\n';
    std::cout << data.u64_data << '\n';
    std::cout << data.fp_data << '\n';
    std::cout << data.dp_data << '\n';

    auto buf = serializer<data_s>::serialize(data);
    auto data2 = serializer<data_s>::deserialize(buf);
    auto data3 = serializer<data_s>::deserialize(buf.byte_ptr());

    std::cout << data2.u8_data << '\n';
    std::cout << data2.u16_data << '\n';
    std::cout << data2.u32_data << '\n';
    std::cout << data2.u64_data << '\n';
    std::cout << data2.fp_data << '\n';
    std::cout << data2.dp_data << '\n';

    std::cout << data3.u8_data << '\n';
    std::cout << data3.u16_data << '\n';
    std::cout << data3.u32_data << '\n';
    std::cout << data3.u64_data << '\n';
    std::cout << data3.fp_data << '\n';
    std::cout << data3.dp_data << '\n';

    return 0;
}
