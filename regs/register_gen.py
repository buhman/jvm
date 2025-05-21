from csv_input import read_input
from generate import renderer
from register import parse_row, group_by_block
import register_java
import register_python
import sys

generators = {
    "java": register_java.generate_classes,
    "python": register_python.generate_decoder,
}

if __name__ == "__main__":
    rows = read_input(sys.argv[1])
    generator_type = sys.argv[2]
    block_name = sys.argv[3]
    package_name = sys.argv[4]
    class_name = sys.argv[5]
    base_address = int(sys.argv[6], 16)
    generator = generators[generator_type]
    blocks = group_by_block(map(parse_row, rows))
    render, out = renderer(indent_length=4)
    render(generator(block_name,
                     package_name,
                     class_name,
                     base_address,
                     blocks))
    sys.stdout.write(out.getvalue())
