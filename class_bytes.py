filenames = [
    "Main.class",
    "java/lang/Object.class",
    "java/io/PrintStream.class",
]

import struct

def sign_extend(value, bits):
    sign_bit = 1 << (bits - 1)
    return (value & (sign_bit - 1)) - (value & sign_bit)

def print_bytearray(buf):
    print("new byte[] {")
    for i in range(len(buf)):
        print(f"{sign_extend(buf[i], 8)},", end=' ')
        if i % 16 == 15:
            print()
    print("};")

for filename in filenames:
    with open(filename, 'rb') as f:
        buf = f.read()
        print_bytearray(buf)
