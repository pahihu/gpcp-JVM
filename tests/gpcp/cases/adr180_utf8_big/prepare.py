#!/usr/bin/env python3
"""ADR-180/188: generate a >1 MiB UTF-8 source (more than one scanner block)."""
from pathlib import Path

header = 'MODULE TUtf8Big;\n  IMPORT CPmain, Console;\n(* '
footer = ' *)\nBEGIN\n  Console.WriteString("ПРИВЕТ");\n  Console.WriteLn()\nEND TUtf8Big.\n'
# 2 bytes per Cyrillic letter => 1.2 MiB of source, i.e. two scanner blocks.
data = (header + 'Ж' * 600000 + footer).encode('utf-8')
Path('TUtf8Big.cp').write_bytes(data)
