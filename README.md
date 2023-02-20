# vnet_serializer

A C++ struct serializer for transmitting structure of data over the network in the 
same standard. The struct is serialized in network endianness, similar to how 
`htonl`, `htons`, `ntohl`, and `ntohs` work, but rather dynamic in size.

On the receiver end, the data is, then, deserialized into the struct.

The user can define any length and any combination of struct of data types as long as
the systems support it.

**Warning**: I'm not sure about the data padding on different system as it hasn't been 
tested yet. You can try it, but I'm quite sure it would work.

For more compression, you can pack the structure using `#pragma pack(1)` to tell the 
compiler to not pad the data, but use 1-byte packaging.

The target of usages is on microcontrollers, bandwidth-limited systems, 
and time-sensitive systems.

Comparing to compressing string and my previously experimental HexTypes, this struct 
serializing method looks more promising and has a plenty of optimization and 
development room.