import sys

from csv_input import read_input
from generate import renderer

from bits import parse_row
from bits import group_by_register_enum
from bits_java import generate_registers

if __name__ == "__main__":
    rows = read_input(sys.argv[1])
    group = group_by_register_enum(map(parse_row, rows))
    render, out = renderer(indent_length=4)
    render(generate_registers("holly", "CoreBits", group))
    sys.stdout.write(out.getvalue())