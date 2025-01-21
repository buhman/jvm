import sys

from generate import renderer
from csv_input import read_input_headerless
from sparse_struct import parse
from sparse_struct_java import render_declarations

from pprint import pprint

_field_types = {
    "parameter_control_word": "int",
    "user_clip_": "int",
    "object_pointer": "int",
    "bounding_box_": "int",
    "isp_tsp_instruction_word": "int",
    "tsp_instruction_word": "int",
    "texture_control_word": "int",
    "data_size_for_sort_dma": "int",
    "next_address_for_sort_dma": "int",
    "face_color_": "float",
    "face_offset_color_": "float",
    "x": "float",
    "y": "float",
    "z": "float",
    "base_color_": "float",
    "base_color_0": "int",
    "base_color_1": "int",
    "offset_color_0": "int",
    "offset_color_1": "int",
    "base_intensity_": "int",
    "u": "float",
    "v": "float",
    "u_v": "int",
    "base_color": "int",
    "offset_color": "int",
    "offset_color_": "float",
    "base_intensity": "float",
    "offset_intensity": "float",
    "a_": "float",
    "b_": "float",
    "c_": "float",
    "d_": "float",
    "a_u_a_v": "int",
    "b_u_b_v": "int",
    "c_u_c_v": "int",
    "_res": "int"
}

def get_type(field_name: str):
    match = None
    match_len = 0
    for name, type in _field_types.items():
        if field_name.startswith(name) and len(name) >= match_len:
            match = type
            assert match_len != len(name), (name, match)
            match_len = len(name)
    assert match != None, field_name
    return match

if __name__ == "__main__":
    rows = read_input_headerless(sys.argv[1])
    package_name = sys.argv[2]
    class_name = sys.argv[3]
    declarations = parse(rows,
                         expected_offset=4,
                         expected_sizes={32, 64})
    render, out = renderer(indent_length=4)
    render(render_declarations(get_type, package_name, class_name, declarations,
                               store_queue_buffer=True,
                               get_byte=False))
    sys.stdout.write(out.getvalue())
