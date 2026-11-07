(*
 * Adapted from oberonc: tests/base/Out4.Mod
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

MODULE Out4;
  IMPORT CPmain, Console;
  TYPE
    R0 = RECORD x, y : INTEGER END;
    R1 = RECORD r0 : R0 END;
    R8 = RECORD x : ARRAY 2 OF INTEGER END;
    R9 = ARRAY 3 OF INTEGER;
    R11 = RECORD v : ARRAY 4 OF R0 END;
    ARR = ARRAY 2 OF R11;
  VAR
    i : INTEGER;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE P0();
    VAR
      a : R8;
      b : R9;
      j : INTEGER;
      r1 : R1;
      s : ARR;
    PROCEDURE P1(o : BOOLEAN ; VAR z0, z2, z3 : INTEGER; VAR z1 : R9; VAR s : ARR);
    BEGIN
      o := TRUE;
      z0 := 20;
      z1[2] := 23;
      z2 := 21;
      z3 := 22;
      z0 := s[i].v[3].x + 6;
      s[i].v[3].x  := z0 + 4;
    END P1;
  BEGIN
    i := 1;
    j := 10;
    WriteInt(j);
    a.x[1] := 11;
    WriteInt(a.x[1]);
    r1.r0.x := 12;
    WriteInt(r1.r0.x);
    b[2] := 13;
    WriteInt(b[2]);
    s[i].v[3].x := 14;
    WriteInt(s[i].v[3].x);
    P1(TRUE, j, a.x[1], r1.r0.x, b, s);
    WriteInt(j);
    WriteInt(a.x[1]);
    WriteInt(r1.r0.x);
    WriteInt(b[2]);
    WriteInt(s[i].v[3].x)
  END P0;

  PROCEDURE P9(o : BOOLEAN ; VAR z0 : INTEGER);
  BEGIN
    o := FALSE;
    z0 := z0 + 1;
    IF z0 # 4 THEN P9(o, z0) END
  END P9;
  PROCEDURE P10(VAR z0 : INTEGER);
  BEGIN
    z0 := z0 + 10
  END P10;

  PROCEDURE P8();
    VAR
      a, i, j : INTEGER;
      s : ARR;
  BEGIN
    a := 1;
    WriteInt(a);
    P9(TRUE, a);
    WriteInt(a);
    i := 1; j := 1;
    s[i*1].v[j-1].x := 90;
    P10(s[i*1].v[j-1].x);
    WriteInt(s[i*1].v[j-1].x)
  END P8;
BEGIN
  P8(); P0()
END Out4.