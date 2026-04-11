#!/usr/bin/env python3

"""
validate.py

This script makes sure that the payload sizes observed in the .BIN file are
consistent with the entry layouts declared in the header section.

It checks that for each device type, the maximum payload size observed
can fit at least one entry of the declared size.

If any device has a declared entry size larger than all observed payloads,
it flags a mismatch, as this would lead to zero rows being parsed for those sections.
"""

import argparse
import re
from collections import defaultdict

SEP = b"\x1c\x1c\x1c\x1c"

TYPE_SIZES = {
    "u8": 1,
    "s8": 1,
    "u16": 2,
    "s16": 2,
    "u32": 4,
    "s32": 4,
    "u64": 8,
    "s64": 8,
    "float": 4,
    "double": 8,
}

DEVICE_RE = re.compile(r"\|\s*([A-Za-z0-9_]+)\s+(.*?)<([0-9A-Fa-f]{8})>\s*\|", re.DOTALL)
FIELD_RE = re.compile(r"<([^,<>]+),([^,<>]+),([^<>]+)>")


def split_sections(data: bytes) -> list[bytes]:
    sections = data.split(SEP)
    if sections and sections[-1] == b"":
        sections.pop()
    return sections


def parse_header(header_bytes: bytes) -> dict[int, dict]:
    header = header_bytes.decode("utf-8", errors="ignore")
    devices: dict[int, dict] = {}

    for match in DEVICE_RE.finditer(header):
        name = match.group(1)
        body = match.group(2)
        id_text = match.group(3)
        dev_id = int(id_text, 16)

        fields = []
        for f_match in FIELD_RE.finditer(body):
            field_name = f_match.group(1).strip()
            field_type = f_match.group(2).strip()
            fields.append((field_name, field_type))

        entry_size = 0
        unknown_types = []
        for _, ftype in fields:
            sz = TYPE_SIZES.get(ftype)
            if sz is None:
                unknown_types.append(ftype)
            else:
                entry_size += sz

        devices[dev_id] = {
            "name": name,
            "id_text": id_text,
            "fields": fields,
            "entry_size": entry_size,
            "unknown_types": sorted(set(unknown_types)),
        }

    return devices


def analyze_file(path: str) -> int:
    with open(path, "rb") as f:
        data = f.read()

    sections = split_sections(data)
    if not sections:
        print("No sections found")
        return 1

    header_map = parse_header(sections[0])
    if not header_map:
        print("Failed to parse any device definitions from header section")
        return 1

    observed_payloads: dict[int, list[int]] = defaultdict(list)
    observed_lengths: dict[int, list[int]] = defaultdict(list)

    for sec in sections[1:]:
        if len(sec) < 5:
            continue
        dev_id = int.from_bytes(sec[0:4], byteorder="little")
        section_len = len(sec)
        payload_len = section_len - 5  # 4-byte ID + 1-byte checksum
        observed_lengths[dev_id].append(section_len)
        observed_payloads[dev_id].append(payload_len)

    print(f"File: {path}")
    print(f"Sections total (including header): {len(sections)}")
    print()

    problems = 0

    for dev_id, meta in sorted(header_map.items()):
        name = meta["name"]
        entry_size = meta["entry_size"]
        id_text = meta["id_text"]
        fields = len(meta["fields"])

        payloads = observed_payloads.get(dev_id, [])
        lengths = observed_lengths.get(dev_id, [])

        print(f"Device {name} (0x{id_text})")
        print(f"  Declared fields: {fields}")
        print(f"  Declared entry size: {entry_size} bytes")

        if meta["unknown_types"]:
            print(f"  Unknown field types in header: {', '.join(meta['unknown_types'])}")

        if not payloads:
            print("  Observed sections: 0")
            print("  Status: no data sections found for this device")
            print()
            continue

        unique_lengths = sorted(set(lengths))
        unique_payloads = sorted(set(payloads))
        min_payload = min(payloads)
        max_payload = max(payloads)
        max_entries = max((p // entry_size) if entry_size > 0 else 0 for p in payloads)

        print(f"  Observed sections: {len(payloads)}")
        print(f"  Section lengths seen: {unique_lengths}")
        print(f"  Payload lengths seen: {unique_payloads}")
        print(f"  Max entries/section from payload//entry_size: {max_entries}")

        if entry_size > 0 and max_payload < entry_size:
            problems += 1
            print("  Status: MISMATCH")
            print(
                "  Reason: header declares an entry larger than every observed payload "
                f"({entry_size} > {max_payload}), so parser computes 0 rows for these sections"
            )
        else:
            print("  Status: OK (payload can fit at least one declared entry)")

        print()

    print(f"Summary mismatches: {problems}")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Check whether header-declared entry layouts fit observed section payload sizes."
    )
    parser.add_argument("input", help="Path to .BIN log file")
    args = parser.parse_args()
    return analyze_file(args.input)


if __name__ == "__main__":
    raise SystemExit(main())
