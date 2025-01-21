def render_fields(get_type, fields):
    for field in fields:
        if field.name.startswith("_res"):
            continue

        field_type = get_type(field.name)
        if field.array_length == 1:
            yield f"public {field_type} {field.name};"
        else:
            for i in range(field.array_length):
                yield f"public {field_type} {field.name}{i};"

def render_constructor(get_type, declaration, store_queue_buffer):
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

    yield "super();"

    for i, field in enumerate(declaration.fields):
        if field.name.startswith("_res"):
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
            continue
        if field.array_length == 1:
            yield f"case {ix}: return {field.name};"
        else:
            for i in range(field.array_length):
                yield f"case {ix + i}: return {field.name}{i};"
        ix += field.array_length
    yield "default: return 0;"
    yield "}"
    yield "}"

def render_submit(get_type, fields):
    yield "public void submit() {"
    for i, field in enumerate(fields):
        index = i * 4
        value = "0" if "_res" in field.name else field.name
        field_type = get_type(field.name)
        if field_type == "int":
            yield f"putInt({index}, {value});"
        elif field_type == "float":
            yield f"putFloat({index}, {value});"
        else:
            assert False, field_type
    yield "Memory.putU4(0xff000038, MemoryMap.ta_fifo_polygon_converter); // QACR0";
    if len(fields) == 16:
        yield "Memory.putU4(0xff00003c, MemoryMap.ta_fifo_polygon_converter); // QACR1";
    if len(fields) == 8:
        yield "SH4Intrinsic.pref1(MemoryMap.store_queue);"
    else:
        yield "SH4Intrinsic.pref2(MemoryMap.store_queue);"

    yield "}"

def render_declaration(get_type, declaration, store_queue_buffer, get_byte):
    yield f"public static class {declaration.name}"
    if store_queue_buffer:
        assert len(declaration.fields) in {8, 16}, len(declaration.fields)
        yield "    extends StoreQueueBuffer"
    if get_byte: # FIXME: hack?
        yield "    implements GdromCommandPacketInterface"
    yield "{"
    yield ""
    yield from render_fields(get_type, declaration.fields)
    yield from render_constructor(get_type, declaration, store_queue_buffer)
    if get_byte:
        yield from render_get_byte(declaration.fields)
    if store_queue_buffer:
        yield from render_submit(get_type, declaration.fields)
    yield "}"

def render_declarations(get_type, package_name, class_name, declarations, *, store_queue_buffer, get_byte):
    yield f"package sega.dreamcast.{package_name};"
    yield ""
    if store_queue_buffer:
        yield "import sega.dreamcast.MemoryMap;"
        yield "import sega.dreamcast.sh7091.StoreQueueBuffer;"
        yield "import jvm.internal.SH4Intrinsic;"
        yield "import jvm.internal.Memory;"
        yield ""
    yield f"public class {class_name} {{"
    for declaration in declarations:
        yield from render_declaration(get_type, declaration, store_queue_buffer, get_byte)
    yield "}"
