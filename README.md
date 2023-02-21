# vnet_serializer

A C++ struct serializer for transmitting structure of data over the network in the 
same standard. The struct is serialized in network endianness, similar to how 
`htonl`, `htons`, `ntohl`, and `ntohs` work, but rather dynamic in struct_size.

On the receiver end, the data is, then, deserialized into the struct.

The user can define any length and any combination of struct of data types as long as
the systems support it.

**Warning**: I'm not sure about the data padding on different system as it hasn't been 
tested yet. You can try it, but I'm quite sure it would work.

The target of usages is on microcontrollers, bandwidth-limited systems, 
and time-sensitive systems.

Comparing to compressing string and my previously experimental HexTypes, this struct 
serializing method looks more promising and has a plenty of optimization and 
development room.

## How to use

* Include the header file `serializer.h` in your project. The namespace is `vnet`.
* For more intuitive examples, you can play with `main.cpp` file to test it for youself.
* I have made some useful `print` functions for representing bits in hex format.
