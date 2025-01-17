from dataclasses import dataclass

class EndOfInput(Exception):
    pass

def next_row(ix, rows, advance):
    if ix >= len(rows):
        raise EndOfInput

    if advance:
        while rows[ix][0] == "":
            ix += 1
            if ix >= len(rows):
                raise EndOfInput
    row = rows[ix]
    ix += 1
    return ix, row

@dataclass
class FieldDeclaration:
    offset: int
    name: str
    default: int
    array_length: str

@dataclass
class StructDeclaration:
    name: str
    fields: list[FieldDeclaration]
    size: int

def parse_type_declaration(ix, rows, expected_offset, expected_sizes):
    ix, row = next_row(ix, rows, advance=True)
    assert len(row) in {2, 3}, row
    struct_name, *empty = row
    assert all(e == "" for e in empty)
    fields = []
    last_offset = 0 - expected_offset
    res_ix = 0

    def terminate():
        size = last_offset + expected_offset
        assert size in expected_sizes, size
        return ix, StructDeclaration(
            struct_name,
            fields,
            size
        )

    seen_names = set()

    while True:
        try:
            ix, row = next_row(ix, rows, advance=False)
        except EndOfInput:
            return terminate()
        if row[0] == "":
            return terminate()
        else:
            default = None
            if len(row) == 2:
                _offset, name = row
            elif len(row) == 3:
                _offset, name, _default = row
                if _default.strip() != "":
                    default = int(_default, 16)
            else:
                assert False, row
            offset = int(_offset, 16)
            assert offset == last_offset + expected_offset, (hex(offset), hex(last_offset), expected_offset)
            last_offset = offset
            if name == "":
                name = f"_res{res_ix}"
                res_ix += 1

            if fields and fields[-1].name == name:
                assert offset == fields[-1].offset + (fields[-1].array_length * expected_offset)
                fields[-1].array_length += 1
            else:
                assert name not in seen_names, row
                seen_names.add(name)
                fields.append(FieldDeclaration(offset, name, default, 1))

def parse(rows, expected_offset, expected_sizes):
    ix = 0
    declarations = []
    while True:
        try:
            ix, declaration = parse_type_declaration(ix, rows, expected_offset, expected_sizes)
        except EndOfInput:
            break
        declarations.append(declaration)

    return declarations
