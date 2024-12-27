from dataclasses import dataclass
from collections import defaultdict

@dataclass
class Register:
    block: str
    address: int
    size: int
    name: str
    rw: set[str]
    description: str

def parse_address(row):
    address = int(row["address"], 16)
    if "offset" in row:
        offset = int(row["offset"], 16)
        address += offset << 16
    return address

def parse_rw(row):
    s = set(row["r/w"])
    assert (s & {"R", "W"}) == s
    return s

blocks_names = set()

def parse_block_name(row):
    global blocks_names
    block = row["block"]
    name = row["name"]
    key = (block, name)
    assert key not in blocks_names
    return block, name

def parse_row(row):
    block, name = parse_block_name(row)
    return Register(
        block=block,
        address=parse_address(row),
        size=int(row["size"]),
        name=name,
        rw=parse_rw(row),
        description=row["description"]
    )

def group_by_block(registers):
    groups = defaultdict(list)
    for register in registers:
        groups[register.block].append(register)
    sorted_groups = []
    for block, registers in groups.items():
        sorted_groups.append(
            (block, list(sorted(registers, key=lambda r: r.address))))
    return list(sorted(sorted_groups, key=lambda g: g[1][0].address))
