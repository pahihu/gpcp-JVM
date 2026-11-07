(*
 * Adapted from oberonc: tests/base/RecordParam.Mod
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

MODULE RecordParam;
  IMPORT CPmain, Console;
  TYPE RP = POINTER TO R;
    R = RECORD
          i: INTEGER;
          p: RP;
        END;
  VAR
  g0, g1, g2: RP;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE Print(x: RP);
  BEGIN
    WriteInt(x.i);
    IF x.p = NIL THEN WriteInt(0) ELSE WriteInt(x.p.i) END;
    WriteLn
  END Print;

  PROCEDURE Init0(VAR x: RP; i: INTEGER);
  BEGIN
    x.i := i;
    NEW(x.p);
    x.p.i := i;
  END Init0;
  
  PROCEDURE Init1(x: RP; i: INTEGER);
  BEGIN
    x.i := i;
    NEW(x.p);
    x.p.i := i;
  END Init1;
  
  PROCEDURE Init2(VAR x: R; i: INTEGER);
  BEGIN
    x.i := i;
    NEW(x.p);
    x.p.i := i;
  END Init2;
  
PROCEDURE Run*;
BEGIN
  NEW(g0);
  g0.p := g0;
  Init0(g0.p, 8);
  Print(g0.p); (* 8 8 *)

  NEW(g1);
  g1.p := g1;
  Init1(g1.p, 8);
  Print(g1.p); (* 8 0 *)

  NEW(g2);
  g2.p := g2;
  Init2(g2.p^, 8);
  Print(g2.p); (* 8 0 *)

END Run;

BEGIN
 Run
END RecordParam.
