import struct

var = struct.pack("hhl", 1, 2, 3)
print(var)
tup = struct.unpack("hhl", var)
print(tup)

var = struct.pack(">ii5s", 1, 2, b"hello")
print(var)
tup = struct.unpack(">ii5s", var)
print(tup)

