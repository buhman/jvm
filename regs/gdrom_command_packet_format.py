import sys

from generate import renderer
from csv_input import read_input_headerless
from sparse_struct import parse
from sparse_struct_java import render_declarations

def get_type(field_name: str):
    return "byte"

if __name__ == "__main__":
    rows = read_input_headerless(sys.argv[1])
    package_name = sys.argv[2]
    class_name = sys.argv[3]
    declarations = parse(rows,
                         expected_offset=1,
                         expected_sizes={12})
    render, out = renderer(indent_length=4)
    render(render_declarations(get_type, package_name, class_name, declarations, want_get_byte=True))
    sys.stdout.write(out.getvalue())
