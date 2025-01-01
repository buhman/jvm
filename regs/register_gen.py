from csv_input import read_input
from generate import renderer
from register import parse_row, group_by_block
from register_java import generate_classes
import sys

if __name__ == "__main__":
    rows = read_input(sys.argv[1])
    block_name = sys.argv[2]
    package_name = sys.argv[3]
    class_name = sys.argv[4]
    base_address = int(sys.argv[5], 16)
    blocks = group_by_block(map(parse_row, rows))
    render, out = renderer(indent_length=4)
    render(generate_classes(block_name,
                            package_name,
                            class_name,
                            base_address,
                            blocks))
    sys.stdout.write(out.getvalue())
