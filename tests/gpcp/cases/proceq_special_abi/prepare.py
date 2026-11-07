#!/usr/bin/env python3
"""Supply the hand-written Java ABI of the -special SpecialProc interface."""

import os
import pathlib
import subprocess

root = pathlib.Path("CP/SpecialProc")
root.mkdir(parents=True, exist_ok=True)

(root / "SpecialProc_Handler.java").write_text(
    """package CP.SpecialProc;

public abstract class SpecialProc_Handler {
    public SpecialProc_Handler() {}
    public abstract void Invoke(int x);
}
""",
    encoding="utf-8",
)

(root / "SpecialProc_Command.java").write_text(
    """package CP.SpecialProc;

public abstract class SpecialProc_Command {
    public SpecialProc_Command() {}
    public abstract void Invoke(int x);
}
""",
    encoding="utf-8",
)

(root / "SpecialProc.java").write_text(
    """package CP.SpecialProc;

public final class SpecialProc {
    private SpecialProc() {}
    public static void Install(SpecialProc_Handler h) { h.Invoke(11); }
    public static void Run(SpecialProc_Command c) { c.Invoke(22); }
}
""",
    encoding="utf-8",
)

subprocess.run(
    ["javac", "-d", ".",
     str(root / "SpecialProc_Handler.java"),
     str(root / "SpecialProc_Command.java"),
     str(root / "SpecialProc.java")],
    check=True,
)