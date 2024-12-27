from register import parse_row, group_by_block
from csv_input import read_input
import sys
from generate import renderer

def generate_register(base_address, register):
    yield f"public static final int {register.name} = {hex(base_address + register.address)};"

def generate_classes(package_name, base_address, blocks):
    yield f"package sega.dreamcast.{package_name};"
    for block, registers in blocks:
        yield f"public class {block.capitalize()} {{"
        for register in registers:
            yield from generate_register(base_address, register)
        yield "}"

if __name__ == "__main__":
    rows = read_input(sys.argv[1])
    blocks = group_by_block(map(parse_row, rows))
    render, out = renderer(indent_length=4)
    holly_base_address = 0xa05f8000
    render(generate_classes("holly", holly_base_address, blocks))
    sys.stdout.write(out.getvalue())
