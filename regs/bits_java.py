from bits import sign_extend
from bits import mask_from_bits

def generate_bit(bit):
    #name = bit.bit_name
    if bit.enum_name == "":
        name = f"{bit.register_name}__{bit.bit_name}".lower()
    else:
        name = f"{bit.register_name}__{bit.enum_name}__{bit.bit_name}".lower()

    if not bit.value and not bit.mask:
        yield f"public static int {name}(int n) {{"
        yield f"return (n >> {min(bit.bits)}) & {sign_extend(mask_from_bits(bit.bits), 32)};"
        yield "}"
    elif bit.value:
        assert (bit.value is None) ^ (bit.mask is None), bit
        yield f"public static final int {name} = {bit.value} << {min(bit.bits)};"
    elif bit.mask:
        assert (bit.value is None) ^ (bit.mask is None), bit
        yield f"public static int {name}(int n) {{"
        if type(bit.mask) is str:
            yield f"return (n & {sign_extend(mask_from_bits(bit.bits), 32)}) << {min(bit.bits)};"
        else:
            yield f"return (n & {bit.mask}) << {min(bit.bits)};"
        yield "}"
    else:
        assert False, bit

def generate_bits(bits):
    for bit in bits:
        yield from generate_bit(bit)

def generate_enums(enum_group):
    for enum_name, bits in enum_group.items():
        if enum_name == "":
            yield from generate_bits(bits)
        else:
            #yield f"public class {enum_name} {{"
            yield from generate_bits(bits)
            #yield "}"

def generate_registers(package_name, class_name, group):
    yield f"package sega.dreamcast.{package_name};"
    yield f"public class {class_name} {{"
    for register_name, enum_group in group.items():
        #yield f"public class {register_name.lower()} {{"
        yield from generate_enums(enum_group)
        #yield "}"
    yield "}"
