(*
 * Adapted from oberonc: tests/base/ConstantFoldingAndLoadOp.Mod
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

MODULE ConstantFoldingAndLoadOp;
  IMPORT CPmain, Console;
  CONST con = 100;
  TYPE
    V = RECORD
          x : ARRAY 10 OF INTEGER;
        END;
  VAR
    i,j : INTEGER;
    c : ARRAY 2 OF INTEGER;
    d : V;
    e : ARRAY 2 OF BOOLEAN;
    b : BOOLEAN;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE PrintBool(x : BOOLEAN);
  BEGIN IF x THEN WriteInt(1) ELSE WriteInt(0) END;
  END PrintBool;
BEGIN
  j := 2;
  c[0] := 3;
  d.x[0] := 4;
  e[0] := TRUE;
  i := 2 * 3 + 10 DIV 2;
  WriteInt(i);
  i := 2*c[0];
  WriteInt(i);
  i := 2*d.x[0];
  WriteInt(i);
  i := 2*con;
  WriteInt(i);
  i := j*c[0];
  WriteInt(i);
  i := j*d.x[0];
  WriteInt(i);
  i := j*con;
  WriteInt(i);
  WriteLn;
  i := c[0] - 2;
  WriteInt(i);
  i := d.x[0] - 2;
  WriteInt(i);
  i := con - 2;
  WriteInt(i);
  i := c[0] - j;
  WriteInt(i);
  i := d.x[0] - j;
  WriteInt(i);
  i := con - j;
  WriteInt(i);
  i := con + 0;
  WriteInt(i);
  i := con - 0;
  WriteInt(i);
  WriteLn;
  b := TRUE & e[0];
  PrintBool(b);
  b := b & e[0];
  PrintBool(b);
  b := e[0] & TRUE;
  PrintBool(b);
  b := e[0] & b;
  PrintBool(b);
  b := (TRUE & e[0]) OR e[0];
  PrintBool(b);
  b := TRUE OR TRUE;
  PrintBool(b);
END ConstantFoldingAndLoadOp.