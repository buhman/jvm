def render_method_definition(get_type, declaration):
    yield "int store_queue = MemoryMap.store_queue;"
    for i, field in enumerate(declaration.fields):
        index = i * 4
        value = "0" if "_res" in field.name else field.name
        field_type = get_type(field.name)
        if field_type == "int":
            yield f"Memory.putU4(store_queue + {index}, {value});"
        elif field_type == "float":
            yield f"Memory.putF4(store_queue + {index}, {value});"
        else:
            assert False, field_type
    yield "Memory.putU4(0xff000038, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR0";
    if len(declaration.fields) == 16:
        yield "Memory.putU4(0xff00003c, ((MemoryMap.ta_fifo_polygon_converter >> 26) & 0b111) << 2); // QACR1";
    if len(declaration.fields) == 8:
        yield "SH4Intrinsic.pref1(store_queue);"
    else:
        yield "SH4Intrinsic.pref2(store_queue);"

def render_method_declaration(get_type, declaration):
    initializer = f"public static void {declaration.name}("
    padding = " " * len(initializer)
    def start(i):
        if i == 0:
            return initializer
        else:
            return padding
    declaration_fields = [f for f in declaration.fields
                          if (not f.name.startswith('_res')
                              and f.default is None
                              )]
    for i, field in enumerate(declaration_fields):
        s = start(i)
        assert field.array_length <= 4, field
        type = get_type(field.name) if field.array_length == 1 else "int"
        comma = ',' if i + 1 < len(declaration_fields) else ''
        yield s + f"{type} {field.name}" + comma

    if declaration_fields:
        yield padding + ') {'
    else:
        yield initializer + ') {'

    yield from render_method_definition(get_type, declaration)

    yield "}"

def render_declarations(get_type, package_name, class_name, declarations):
    yield f"package sega.dreamcast.{package_name};"
    yield ""
    yield "import sega.dreamcast.MemoryMap;"
    yield "import jvm.internal.SH4Intrinsic;"
    yield "import jvm.internal.Memory;"
    yield ""
    yield f"public class {class_name} {{"
    for declaration in declarations:
        yield from render_method_declaration(get_type, declaration)
    yield "}"
