from dataclasses import dataclass
from typing import Union
from collections import defaultdict

def parse_bit_number(s):
    assert '-' not in s, s
    assert ',' not in s, s
    return int(s, 10)

def parse_bit_set(s, split_char, maxsplit):
    #assert len(list(c for c in s if c == split_char)) == 1, s
    split = list(map(parse_bit_number, s.split(split_char, maxsplit=maxsplit)))
    for i in range(len(split) - 1):
        left = split[i]
        right = split[i+1]
        assert left > right, (left, right)
    return split

def parse_bit_range(s):
    if '-' in s:
        left, right = parse_bit_set(s, '-', 1)
        return set(range(right, left+1))
    elif ',' in s:
        bits = parse_bit_set(s, ',', -1)
        return set(bits)
    else:
        num = parse_bit_number(s)
        return set([num])

assert parse_bit_range("4-0") == {4, 3, 2, 1, 0}

def mask_from_bits(bits):
    mask = 0
    for b in bits:
        mask |= 1 << b
    mask >>= min(bits)
    return mask

assert mask_from_bits({4, 2}) == 5

def _parse_value(s):
    if s == "":
        return None
    if s.startswith("0x"):
        return int(s[2:], 16)
    if s.startswith("0b"):
        return int(s[2:], 2)
    if s.startswith("float_"):
        return s
    return int(s, 10)

def sign_extend(x, b):
    m = 1 << (b - 1)
    x = x & ((1 << b) - 1)
    r = (x ^ m) - m;
    return r

def parse_value(s):
    n = _parse_value(s)
    if type(n) is int:
        return sign_extend(n, 32)
    else:
        return n

@dataclass
class Bit:
    register_name: str
    enum_name: str
    bits: set[int]
    bit_name: str
    value: int
    mask: Union[int, str]

@dataclass
class Enum:
    enum_name: str
    bits: list[Bit]

@dataclass
class Register:
    register_name: str
    enums: list[Enum]

def parse_row(row):
    return Bit(
        register_name=row["register_name"],
        enum_name=row["enum_name"],
        bits=parse_bit_range(row["bits"]),
        bit_name=row["bit_name"],
        value=parse_value(row["value"]),
        mask=parse_value(row["mask"]),
    )

def group_by_register_enum(bits):
    group = defaultdict(lambda: defaultdict(list))
    for bit in bits:
        group[bit.register_name][bit.enum_name].append(bit)
    return group
