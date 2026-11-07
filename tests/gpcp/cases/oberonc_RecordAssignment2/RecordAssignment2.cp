(*
 * Adapted from oberonc: tests/base/RecordAssignment2.Mod
 * https://github.com/lboasso/oberonc
 *
 * MIT License
 *
 * Copyright (c) 2017 Luca Boasso
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Changes for GPCP / Component Pascal:
 *   - Oberon-07 WriteInt/WriteChar/WriteString/WriteLn replaced by Console output.
 *   - CPmain import added so the module body runs.
 *)

MODULE RecordAssignment2;
  IMPORT CPmain, Console;
  TYPE RP = POINTER TO R;
    R = RECORD
          i: INTEGER;
          a: ARRAY 10 OF RP;
          p: RP;
        END;
  VAR
  gbl0, gbl1 : RP;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE Init(VAR x: R; i: INTEGER);
  BEGIN
    x.i := i;
    NEW(x.a[2]);
    x.a[2].i := i;
    NEW(x.p);
    x.p.i := i;
  END Init;

  PROCEDURE Print(x: R);
  BEGIN
    WriteInt(x.i);
    WriteInt(x.a[2].i);
    WriteInt(x.p.i);
    WriteLn
  END Print;

  PROCEDURE Run(local: RP; x: R);
    VAR y: R;
  BEGIN
    Init(y, 1);
    y := x;
    Print(y); (* 8   8   8 *)

    Init(gbl0^, 2);
    gbl0^ := x;
    Print(gbl0^); (* 8   8   8 *)

    Init(gbl0^, 3);
    gbl0^ := local^;
    Print(gbl0^); (* 8   8   8 *)

    Init(gbl0^.a[2]^, 4);
    gbl0^.a[2]^ := local^;
    Print(gbl0^.a[2]^); (* 8   8   8 *)

    Init(gbl0^.p^, 5);
    gbl0^.p^ := local^;
    Print(gbl0^.p^); (* 8   8   8 *)

    Init(gbl0^.p^.p^, 6);
    gbl0^.p^.p^ := local^;
    Print(gbl0^.p^.p^) (* 8   8   6 *)

  END Run;

BEGIN
  NEW(gbl0); NEW(gbl1);
  Init(gbl1^, 8);
  Run(gbl1, gbl1^)
END RecordAssignment2.
