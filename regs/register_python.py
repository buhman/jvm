def generate_dataclass(block_name, registers):
    yield "@dataclass"
    yield f"class {block_name.capitalize()}:"
    for register in registers:
        if register.size == 4:
            yield f"    {register.name}: int"
        elif register.size > 4:
            yield f"    {register.name}: list[int]"
        else:
            assert False, register.size
    yield ""
    yield "    def __init__(self):"
    yield "        pass"
    yield ""
    yield "    def __repr__(self):"
    yield '        return (f"{self.__class__.__qualname__}(" +'
    yield '        ",\\n      ".join(['
    for register in registers:
        if register.size == 4:
            yield f'            f"{register.name}={{self.{register.name}:08x}}",'
        elif register.size > 4:
            #yield f'            (f"{register.name}=" + ",\\n".join(['
            #yield f'                f"{{i:08x}}" for i in self.{register.name}'
            #yield "            ])),"
            pass
        else:
            assert False, register.size
    yield '        ]) +'
    yield '        ")")'
    yield ""

def generate_struct_decoder(block_name, registers):
    yield f"def decode_{block_name.lower()}(buf: bytes) -> {block_name.capitalize()}:"
    yield "    mem = memoryview(buf)"
    yield f"    {block_name.lower()} = {block_name.capitalize()}()"
    for register in registers:
        lhs = f"{block_name.lower()}.{register.name}"
        mem = f"{hex(register.address)}:{hex(register.address + register.size)}"
        if register.size == 4:
            yield f"    {lhs}, = struct.unpack('<I', mem[{mem}])"
        elif register.size > 4:
            assert register.size % 4 == 0, register.size
            length = register.size // 4
            fmt = f"('I' * {length})"
            yield f"    {lhs} = struct.unpack('<' + {fmt}, mem[{mem}])"
        else:
            assert False, register.size
    yield f"    return {block_name.lower()}"
    yield ""

def generate_decoder(block_name, package_name, class_name, base_address, blocks):
    yield "from dataclasses import dataclass"
    yield "import struct"
    yield ""
    for block, registers, in blocks:
        if block.lower() != block_name.lower():
            continue
        yield from generate_dataclass(block_name, registers)
        yield from generate_struct_decoder(block_name, registers)
