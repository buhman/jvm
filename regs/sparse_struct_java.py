def render_fields(get_type, fields):
    for field in fields:
        field_type = get_type(field.name)
        assert field.array_length == 1
        yield f"public {field_type} {field.name};"

def render_constructor(get_type, declaration):
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
        type = get_type(field.name) if field.array_length == 1 else "uint32_t"
        comma = ',' if i + 1 < len(constructor_fields) else ''
        yield s + f"{type} {field.name}" + comma

    if constructor_fields:
        yield padding + ') {'
    else:
        yield initializer + ') {'

    for i, field in enumerate(declaration.fields):
        value = field.name if not field.name.startswith('_res') else '0'
        value = hex(field.default) if field.default is not None else value
        s = ':' if i == 0 else ','
        yield f"this.{field.name} = {value};"

    yield "}"

    array_fields = [f for f in declaration.fields
                    if f.array_length > 1]

def render_declaration(get_type, declaration):
    yield f"public class {declaration.name} {{"
    yield from render_fields(get_type, declaration.fields)
    yield from render_constructor(get_type, declaration)
    yield "}"

def render_declarations(get_type, package_name, class_name, declarations):
    yield f"package sega.dreamcast.{package_name};"
    yield ""
    yield f"public class {class_name} {{"
    for declaration in declarations:
        yield from render_declaration(get_type, declaration)
    yield "}"
