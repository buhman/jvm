import struct
import sys
from binascii import hexlify

def parse_row(s):
    a, b, c, d = s.strip().split(',')
    return int(a), c, int(d)

def parse_opcode_table(buf):
    rows = [parse_row(i) for i in buf.strip().split('\n')]
    return {opcode: (name, args) for opcode, name, args in rows}

with open('opcodes.csv', 'r') as f:
    opcode_table = parse_opcode_table(f.read())

def size_to_format(size):
    if size == 4:
        return ">I"
    elif size == 2:
        return ">H"
    elif size == 1:
        return ">B"
    else:
        assert False, size

def field(buf, size):
    format = size_to_format(size)
    value, = struct.unpack(format, buf[0:size])
    return buf[size:], value

constant_lookup = {
    7: ("CONSTANT_Class", [("name_index", 2)]),
    9: ("CONSTANT_Fieldref", [("class_index", 2), ("name_and_type_index", 2)]),
    10: ("CONSTANT_Methodref", [("class_index", 2), ("name_and_type_index", 2)]),
    11: ("CONSTANT_InterfaceMethodref", [("class_index", 2), ("name_and_type_index", 2)]),
    8: ("CONSTANT_String", [("string_index", 2)]),
    3: ("CONSTANT_Integer", [("bytes", 4)]),
    4: ("CONSTANT_Float", [("bytes", 4)]),
    5: ("CONSTANT_Long", [("high_bytes", 4), ("low_bytes", 4)]),
    6: ("CONSTANT_Double", [("high_bytes", 4), ("low_bytes", 4)]),
    12: ("CONSTANT_NameAndType", [("name_index", 2), ("descriptor_index", 2)]),
    1: ("CONSTANT_Utf8", [("length", 2), ("bytes", 0)]),
    15: ("CONSTANT_MethodHandle", [("reference_kind", 2), ("reference_index", 2)]),
    16: ("CONSTANT_MethodType", [("descriptor_index", 2)]),
    18: ("CONSTANT_InvokeDynamic", [("bootstrap_method_attr_index", 2), ("name_and_type_index", 2)]),
}


def parse_cp_info(buf):
    buf, tag = field(buf, 1)
    assert tag in constant_lookup, tag
    name, fields = constant_lookup[tag]
    d = {}
    last_value = None
    for field_name, field_size in fields:
        if field_size == 0:
            value = bytes(buf[0:last_value])
            buf = buf[last_value:]
        else:
            buf, value = field(buf, field_size)
            last_value = value
        d[field_name] = value
    return buf, (name, d)

def parse_attribute_info(buf):
    buf, attribute_name_index = field(buf, 2)
    buf, attribute_length = field(buf, 4)
    info = bytes(buf[0:attribute_length])
    buf = buf[attribute_length:]
    return buf, (attribute_name_index, attribute_length, info)

def parse_field_info(buf):
    buf, access_flags = field(buf, 2)
    buf, name_index = field(buf, 2)
    buf, descriptor_index = field(buf, 2)
    buf, attributes_count = field(buf, 2)
    attributes = []
    for i in range(attributes_count):
        buf, attribute = parse_attribute_info(buf)
        attributes.append(attribute)
    return buf, (access_flags, name_index, descriptor_index, attributes_count, attributes)

def parse_exception_table(buf, indent):
    exception_table = [
        ("start_pc", 2),
        ("end_pc", 2),
        ("handler_pc", 2),
        ("catch_type", 2),
    ]
    for name, size in exception_table:
        buf, value = field(buf, size)
        print(indent, name, value)
    return buf

def dump_opcodes(buf, indent):
    ix = 0
    while len(buf) > 0:
        op = buf[0]
        name, arg_length = opcode_table[op]
        buf = buf[1:]
        args = list(buf[0:arg_length])
        print(indent, f"{ix:> 3}", name, args)
        ix += 1 + arg_length
        buf = buf[arg_length:]

def print_code_info(buf, indent, constant_pool):
    code_attribute = [
        ("max_stack", 2),
        ("max_locals", 2),
        ("code_length", 4),
        ("code", 0),
        ("exception_table_length", 2),
        ("exception_table", 0),
        ("attributes_count", 2),
        ("attributes", 0)
    ]
    last_value = None
    for name, size in code_attribute:
        if name == "code":
            print(indent, "code:")
            size = last_value
            dump_opcodes(buf[0:last_value], indent + "  ")
            buf = buf[last_value:]
        elif name == "exception_table":
            print(indent, "exception_table:")
            for i in range(last_value):
                buf = parse_exception_table(buf, indent + "  ")
        elif name == "attributes":
            print(indent, "attributes:")
            for i in range(last_value):
                buf, attribute_info = parse_attribute_info(buf)
                print(indent + "  ", f"attribute {i}:")
                attribute_name_index, attribute_length, info = attribute_info

                constant_type, constant = constant_pool[attribute_name_index - 1]
                assert constant_type == 'CONSTANT_Utf8', constant_type
                attribute_name_bytes = constant["bytes"]

                print(indent + "    ", "attribute_name_index", attribute_name_index, attribute_name_bytes)
                print(indent + "    ", "attribute_length", attribute_length)
                print(indent + "    ", "info", info)
        else:
            buf, value = field(buf, size)
            last_value = value
            print(indent, name, value)
    assert len(buf) == 0

def parse_class(buf):
    buf, magic = field(buf, 4)
    buf, minor_version = field(buf, 2)
    buf, major_version = field(buf, 2)
    buf, constant_pool_count = field(buf, 2)

    print("magic", hex(magic))
    print("minor_version", minor_version)
    print("major_version", major_version)
    print("constant_pool_count", constant_pool_count)

    print("constant_pool:")
    constant_pool = []
    for i in range(constant_pool_count - 1):
        buf, cp_info = parse_cp_info(buf)
        constant_pool.append(cp_info)
        print(i + 1, cp_info)

    buf, access_flags = field(buf, 2)
    buf, this_class = field(buf, 2)
    buf, super_class = field(buf, 2)
    buf, interfaces_count = field(buf, 2)

    print("access_flags", hex(access_flags))
    print("this_class", this_class)
    print("super_class", super_class)
    print("interfaces_count", interfaces_count)

    print("interfaces:")
    for i in range(interfaces_count):
        buf, interface = field(buf, 2)
        print(i, interface)

    buf, fields_count = field(buf, 2)
    print("fields_count", fields_count)
    for i in range(fields_count):
        buf, field_info = parse_field_info(buf)
        print(i, field_info)

    buf, methods_count = field(buf, 2)
    print("methods_count", methods_count)
    print("methods:")
    for i in range(methods_count):
        buf, method_info = parse_field_info(buf)
        print(f"  method {i}:")
        access_flags, name_index, descriptor_index, attributes_count, attributes = method_info
        print("    access_flags", hex(access_flags))

        constant_type, constant = constant_pool[name_index - 1]
        assert constant_type == 'CONSTANT_Utf8', constant_type
        name_bytes = constant["bytes"]

        print("    name_index", name_index, name_bytes)

        constant_type, constant = constant_pool[descriptor_index - 1]
        assert constant_type == 'CONSTANT_Utf8', constant_type
        descriptor_bytes = constant["bytes"]

        print("    descriptor_index", descriptor_index, descriptor_bytes)
        print("    attributes_count", attributes_count)
        print("    attributes:")
        for j in range(attributes_count):
            print(f"    attribute {j}:")
            attribute_name_index, attribute_length, info = attributes[j]

            constant_type, constant = constant_pool[attribute_name_index - 1]
            assert constant_type == 'CONSTANT_Utf8', constant_type
            attribute_name_bytes = constant["bytes"]

            print("      attribute_name_index", attribute_name_index, attribute_name_bytes)
            print("      attribute_length", attribute_length)
            #print("      info", info)
            if attribute_name_bytes == b'Code':
                print_code_info(info, "        ", constant_pool)

    buf, attributes_count = field(buf, 2)
    print("attributes_count", attributes_count)
    print("attributes:")
    for i in range(attributes_count):
        buf, attribute_info = parse_attribute_info(buf)
        print(i, attribute_info)

    assert len(buf) == 0, bytes(buf)

filename = sys.argv[1]

with open(filename, 'rb') as f:
    buf = f.read()

parse_class(memoryview(buf))
