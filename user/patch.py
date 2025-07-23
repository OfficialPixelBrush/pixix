#!/usr/bin/env python3

import sys
import struct
import shutil
from typing import BinaryIO, List, Tuple

def read_struct(fmt: str, file: BinaryIO) -> Tuple:
    size = struct.calcsize(fmt)
    return struct.unpack(fmt, file.read(size))

def write_struct(fmt: str, file: BinaryIO, values: Tuple):
    data = struct.pack(fmt, *values)
    file.write(data)

def align_down(val: int, align: int) -> int:
    return val & ~(align - 1)

def align_up(val: int, align: int) -> int:
    return (val + align - 1) & ~(align - 1)

if len(sys.argv) < 3:
    print(f"Usage: {sys.argv[0]} input.elf output.elf")
    sys.exit(1)

infile_path = sys.argv[1]
outfile_path = sys.argv[2]

with open(infile_path, 'rb') as f:
    e_ident = f.read(16)
    if e_ident[:4] != b'\x7fELF':
        sys.exit("Not an ELF file.")
    elf_class = e_ident[4]
    elf_data = e_ident[5]

    if elf_class != 1:
        sys.exit("Only 32-bit ELF supported.")
    if elf_data != 1:
        sys.exit("Only little-endian ELF supported.")

    f.seek(0)
    full_data = f.read()

# Parse 32-bit ELF Header
ELF_HDR_FMT = "<16sHHLLLLLHHHHHH"
elf_hdr = struct.unpack(ELF_HDR_FMT, full_data[:52])
(
    ident, e_type, e_machine, e_version, e_entry, e_phoff, e_shoff,
    e_flags, e_ehsize, e_phentsize, e_phnum, e_shentsize,
    e_shnum, e_shstrndx
) = elf_hdr

# Read program headers
ph_table = []
for i in range(e_phnum):
    ph_offset = e_phoff + i * e_phentsize
    ph_fmt = "<LLLLLLLL"
    ph = struct.unpack(ph_fmt, full_data[ph_offset:ph_offset+32])
    ph_table.append(list(ph))  # convert to mutable list

# Find the first PT_LOAD segment
PT_LOAD = 1
first_load = None
for ph in ph_table:
    if ph[0] == PT_LOAD:
        first_load = ph
        break

if not first_load:
    sys.exit("No PT_LOAD segment found.")

old_offset = first_load[1]  # p_offset
new_offset = align_up(52 + e_phentsize * e_phnum, 0x100)  # place right after headers
shift_amount = old_offset - new_offset

print(f"Shifting first segment from offset {hex(old_offset)} -> {hex(new_offset)}")

# Prepare new output
with open(outfile_path, 'wb') as out:
    # Copy ELF header + program headers
    out.write(full_data[:e_phoff])

    # Write updated program headers
    for ph in ph_table:
        if ph[0] == PT_LOAD:
            ph[1] -= shift_amount  # p_offset
        else:
            if ph[1] >= old_offset:
                ph[1] -= shift_amount  # shift other offsets too if after
        out.write(struct.pack("<LLLLLLLL", *ph))

    # Copy data before first PT_LOAD (none expected)
    out.write(full_data[e_phoff + e_phentsize * e_phnum:old_offset])

    # Copy loadable segments with shifted offset
    out.write(full_data[old_offset:])

    # Done. Truncate to remove old padding
    out.flush()
    out.truncate()

print(f"Written to {outfile_path}")
