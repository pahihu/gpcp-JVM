(*
 * Adapted from oberonc: tests/base/Out1.Mod
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

MODULE Out1;
  IMPORT CPmain, Console;
  CONST con = 100;
  VAR           
      a : ARRAY 4 OF INTEGER;
      b : ARRAY 3 OF ARRAY 5 OF INTEGER;
      c : ARRAY 4 OF INTEGER;
      i, j : INTEGER;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

BEGIN 
  i := 1;
  j := 2;
  a[j] := 1;
  WriteInt(a[j]);
  a[2] := 2;
  WriteInt(a[2]);
  a[i+j] := 3;
  WriteInt(a[i+j]);
  b[i][j] := 4;
  WriteInt(b[i][j]);
  b[2][4] := 5;
  WriteInt(b[2][4]);
  a[a[i]] := 6;
  WriteInt(a[a[i]]);
  a[c[i]] := 7;
  WriteInt(a[c[i]]);
END Out1.