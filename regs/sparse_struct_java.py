def render_fields(get_type, fields, want_get_byte):
    for field in fields:
        if want_get_byte and field.name.startswith("_res"):
            continue

        field_type = get_type(field.name)
        if field.array_length == 1:
            yield f"public {field_type} {field.name};"
        else:
            for i in range(field.array_length):
                yield f"public {field_type} {field.name}{i};"

def render_constructor(get_type, declaration, want_get_byte):
    initializer = f"public {declaration.name}("
    padding = " " * len(initializer)
    def start(i):
        if i == 0:
            return initializer
        else:
            return padding
    constructor_fields = [f for f in declaration.fields
                          if (not f.name.startswith('_res')
                              and f.default is None
                              )]
    for i, field in enumerate(constructor_fields):
        s = start(i)
        assert field.array_length <= 4, field
        type = get_type(field.name) if field.array_length == 1 else "int"
        comma = ',' if i + 1 < len(constructor_fields) else ''
        yield s + f"{type} {field.name}" + comma

    if constructor_fields:
        yield padding + ') {'
    else:
        yield initializer + ') {'

    for i, field in enumerate(declaration.fields):
        if want_get_byte and field.name.startswith("_res"):
            continue

        value = field.name if not field.name.startswith('_res') else '0'
        value = hex(field.default) if field.default is not None else value
        s = ':' if i == 0 else ','
        if field.array_length == 1:
            yield f"this.{field.name} = {value};"
        else:
            max_shift = 8 * (field.array_length - 1)
            for i in range(field.array_length):
                shift = max_shift - (i * 8)
                yield f"this.{field.name}{i} = ({field.name} >> {shift}) & 0xff;"

    yield "}"

    array_fields = [f for f in declaration.fields
                    if f.array_length > 1]

def render_get_byte(fields):
    ix = 0
    yield "public int getByte(int ix) {"
    yield "switch (ix) {"
    for field in fields:
        if "_res" in field.name:
            pass
        elif field.array_length == 1:
            yield f"case {ix}: return {field.name};"
        else:
            for i in range(field.array_length):
                yield f"case {ix + i}: return {field.name}{i};"
        ix += field.array_length
    yield "default: return 0;"
    yield "}"
    yield "}"

def render_declaration(get_type, declaration, want_get_byte):
    yield f"public static class {declaration.name} implements GdromCommandPacketInterface {{"
    yield from render_fields(get_type, declaration.fields, want_get_byte)
    yield from render_constructor(get_type, declaration, want_get_byte)
    if want_get_byte:
        yield from render_get_byte(declaration.fields)
    yield "}"

def render_declarations(get_type, package_name, class_name, declarations, want_get_byte=False):
    yield f"package sega.dreamcast.{package_name};"
    yield ""
    yield f"public class {class_name} {{"
    for declaration in declarations:
        yield from render_declaration(get_type, declaration, want_get_byte)
    yield "}"
