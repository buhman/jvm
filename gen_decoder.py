import io
import sys
from dataclasses import dataclass
import csv
from pprint import pprint

@dataclass
class Argument:
    signed: bool
    size: int
    name: str

@dataclass
class Instruction:
    code: int
    mnemonic: str
    arguments_size: int
    arguments: list[Argument]

def parse_arguments(types, arguments):
    types = types.strip()
    arguments = arguments.strip()
    if not types:
        assert not arguments
        return 0, []

    types = types.split(',')
    arguments = arguments.split(',')
    assert len(types) == len(arguments), (types, arguments)

    total_size = 0
    l = list(zip(types, arguments))
    args = []
    for i, (type, name) in enumerate(l):
        signed = None
        if type.startswith('v'):
            assert i == (len(l) - 1), l
            assert name == '_', name
            total_size += int(type.removeprefix('v'))
            continue
        elif type.startswith('s'):
            size = int(type.removeprefix('s'))
            signed = True
        elif type.startswith('u'):
            size = int(type.removeprefix('u'))
            signed = False
        else:
            assert False, (type, argument)

        assert size in {1, 2, 4}
        assert signed is not None
        if name in {"byte", "branch", "_const"}:
            assert signed == True, name
        else:
            assert signed == False, name

        total_size += size
        args.append(Argument(
            signed=signed,
            size=size,
            name=name,
        ))

    return total_size, args

def parse_row(row):
    code, _, mnemonic, types, arguments = row

    if types.strip() == '-1':
        arguments_size = -1;
        arguments = arguments.split(',')
    else:
        arguments_size, arguments = parse_arguments(types, arguments)

    yield Instruction(
        code=int(code),
        mnemonic=mnemonic,
        arguments_size=arguments_size,
        arguments=arguments
    )

def parse_opcode_table():
    with open('opcodes.csv', 'r') as f:
        reader = csv.reader(f, delimiter=",", quotechar='"')
        instructions = [instruction for row in reader for instruction in parse_row(row)]
    return instructions

opcode_table = list(sorted(parse_opcode_table(), key=lambda i: i.code))

sign_type_table = {
    (True, 4): "_s4",
    (True, 2): "_s2",
    (True, 1): "_s1",
    (False, 4): "_u4",
    (False, 2): "_u2",
    (False, 1): "_u1",
}

def generate_print_fixed_width_instruction(instruction):
    offset = 1
    for argument in instruction.arguments:
        c_type = "int32_t" if argument.signed else "uint32_t"
        conversion = sign_type_table[(argument.signed, argument.size)]
        yield f"{c_type} {argument.name} = {conversion}(&code[pc + {offset}]);"
        offset += argument.size

    argument_format = ", ".join(
        f"%{'d' if argument.signed else 'u'}"
        for argument in instruction.arguments
    )
    argument_values = ", ".join(
        argument.name
        for argument in instruction.arguments
    )
    if argument_values:
        argument_values = ", " + argument_values
    mnemonic = instruction.mnemonic.ljust(13)
    yield f'printf("%4d: {mnemonic} {argument_format}\\n", pc{argument_values});'
    yield f"return pc + {1 + instruction.arguments_size};"

def generate_print_variable_width_instruction(instruction):
    n = '' if instruction.mnemonic == "wide" else '\\n'
    mnemonic = instruction.mnemonic.ljust(13)
    yield f"{instruction.mnemonic.upper()}_ARGS;"
    yield f'printf("%4d: {mnemonic} {{{n}", pc);'
    yield f"{instruction.mnemonic.upper()}_PRINT_ARGS();"
    yield f'printf("}}{n}\\n");'
    yield f"return {instruction.mnemonic.upper()}_NEXT_PC;"

def generate_print_decoder():
    yield "uint32_t decode_print_instruction(const uint8_t * code, uint32_t pc)"
    yield "{"
    yield "switch (code[pc]) {"
    for instruction in opcode_table:
        yield f"case {instruction.code}: // {instruction.mnemonic}"
        yield "{"

        if instruction.arguments_size == -1:
            yield from generate_print_variable_width_instruction(instruction)
        else:
            yield from generate_print_fixed_width_instruction(instruction)

        yield "}"

    yield "default:"
    yield "{"
    yield "assert(false);"
    yield "return pc;"
    yield "}"
    yield "}"
    yield "}"

def generate_execute_fixed_width_instruction(instruction):
    offset = 1
    for argument in instruction.arguments:
        c_type = "int32_t" if argument.signed else "uint32_t"
        conversion = sign_type_table[(argument.signed, argument.size)]
        yield f"{c_type} {argument.name} = {conversion}(&code[pc + {offset}]);"
        offset += argument.size
    yield f"vm->current_frame->next_pc = pc + {1 + instruction.arguments_size};"
    argument_values = ", ".join(
        argument.name
        for argument in instruction.arguments
    )
    if argument_values:
        argument_values = ", " + argument_values
    yield f"op_{instruction.mnemonic}(vm{argument_values});"

def generate_execute_variable_width_instruction(instruction):
    yield f"{instruction.mnemonic.upper()}_ARGS;"
    argument_values = ", ".join(
        argument
        for argument in instruction.arguments
    )
    if instruction.mnemonic != "wide":
        yield f"vm->current_frame->next_pc = {instruction.mnemonic.upper()}_NEXT_PC;"
    if argument_values:
        argument_values = ", " + argument_values
    if instruction.mnemonic == "wide":
        yield "WIDE_IMPL();"
    else:
        yield f"op_{instruction.mnemonic}(vm{argument_values});"

def generate_execute_decoder():
    yield "void decode_execute_instruction(struct vm * vm, const uint8_t * code, uint32_t pc)"
    yield "{"
    yield "switch (code[pc]) {"
    for instruction in opcode_table:
        yield f"case {instruction.code}: // {instruction.mnemonic}"
        yield "{"

        if instruction.arguments_size == -1:
            yield from generate_execute_variable_width_instruction(instruction)
        else:
            yield from generate_execute_fixed_width_instruction(instruction)

        yield "break;"
        yield "}"
    yield "default:"
    yield "{"
    yield "assert(false);"
    yield "break;"
    yield "}"
    yield "}"
    yield "}"

def should_autonewline(line):
    return (
        "static_assert" not in line
        and "extern" not in line
        and (len(line.split()) < 2 or line.split()[1] != '=') # hacky; meh
    )

def _render(out, lines):
    indent = " "
    level = 0
    namespace = 0
    for l in lines:
        if l and (l[0] == "}" or l[0] == ")"):
            level -= 2
            if level < 0:
                assert namespace >= 0
                namespace -= 1
                level = 0

        if len(l) == 0:
            out.write("\n")
        else:
            out.write(indent * level + l + "\n")

        if l and (l[-1] == "{" or l[-1] == "("):
            if l.startswith("namespace"):
                namespace += 1
            else:
                level += 2

        if level == 0 and l and l[-1] == ";":
            if should_autonewline(l):
                out.write("\n")
    return out

def renderer():
    out = io.StringIO()
    def render(lines):
        return _render(out, lines)
    return render, out

if __name__ == "__main__":
    render, out = renderer()
    render(generate_print_decoder())
    render(generate_execute_decoder())
    sys.stdout.write(out.getvalue())
