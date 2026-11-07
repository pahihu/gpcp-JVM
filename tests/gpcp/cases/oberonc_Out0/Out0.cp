(*
 * Adapted from oberonc: tests/base/Out0.Mod
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

MODULE Out0;
  IMPORT CPmain, Console;
  CONST con = 100;
 TYPE
    V = RECORD  x : ARRAY 10 OF INTEGER END;
    Hello = RECORD world : INTEGER; x : ARRAY 3 OF ARRAY 10 OF V; END;
    int = INTEGER;
    ARR = ARRAY 9 OF int;
    ARR2 = ARRAY 9 OF V;
  VAR
      a : ARRAY 4 OF INTEGER;
      b : ARRAY 3 OF ARRAY 5 OF INTEGER;
      c : ARRAY 1 OF ARRAY 2 OF ARRAY 3 OF ARRAY 4 OF INTEGER;
      d : V;
      e : Hello;
      f : int;
      g : ARR;
      h : ARR2;
      z : RECORD y : int END;
      i, j : INTEGER;
      k : BOOLEAN;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

BEGIN
  a[2] := 8;
  WriteInt(a[2]);
  b[2][3] := 9;
  WriteInt(b[2][3]);
  c[0][1][2][3] := 10;
  WriteInt(c[0][1][2][3]);
  d.x[9] := 11;
  WriteInt(d.x[9]);
  e.world := 12;
  WriteInt(e.world);
  e.x[2][3].x[3] := 13;
  WriteInt(e.x[2][3].x[3]);
  f := 14;
  WriteInt(f);
  g[6] := 15;
  WriteInt(g[6]);
  h[8].x[2] := 16;
  WriteInt(h[8].x[2]);
  z.y := 17;
  WriteInt(z.y);
  i := -z.y + c[0][1][2][3] + h[8].x[2] * e.x[2][3].x[3] -1;
  WriteInt(i);
  j := 2;
  k := (i = j) OR (i >= j);
  IF k THEN WriteInt(1) END
END Out0.