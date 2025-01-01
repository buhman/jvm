def generate_register(base_address, register):
    yield f"public static final int {register.name} = {hex(base_address + register.address)};"

def generate_classes(block_name, package_name, class_name, base_address, blocks):
    yield f"package sega.dreamcast.{package_name};"
    for block, registers in blocks:
        if block.lower() != block_name.lower():
            continue
        yield f"public class {class_name} {{"
        for register in registers:
            yield from generate_register(base_address, register)
        yield "}"
