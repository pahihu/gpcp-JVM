(*
 * Adapted from oberonc: tests/base/ProcVariables0.Mod
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
 *   - Oberon-07 WriteInt/WriteChar/WriteLn replaced by Console output (width 4).
 *   - BEGIN added where Oberon-07 allows a bare RETURN body.
 *   - Final WriteLn added so the expected file ends with a newline.
 *)

MODULE TProcVariables0Ref;
  IMPORT CPmain, Console;
  TYPE
    MyFun = PROCEDURE(): INTEGER;
    R = RECORD i: INTEGER END;
    P = POINTER TO R;
  VAR
    a: MyFun;
    b: PROCEDURE(r: R): P;
    c: PROCEDURE(f: R): P;
    r: R;
    p: P;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE getNum8(): INTEGER;
  BEGIN RETURN 8 END getNum8;

  PROCEDURE getNum7(): INTEGER;
  BEGIN RETURN 7 END getNum7;

  PROCEDURE getPtr0(x: R): P;
    VAR y: P;
  BEGIN
    NEW(y);
    y.i := x.i;
    RETURN y
  END getPtr0;

  PROCEDURE getPtr1(x: R): P;
    VAR y: P;
  BEGIN
    NEW(y);
    y.i := x.i + 1;
    RETURN y
  END getPtr1;

  PROCEDURE Run;
    VAR
      a0: MyFun;
      b0: PROCEDURE(r: R): P;
      c0: PROCEDURE(f: R): P;
      r0: R;
      p0: P;
  BEGIN
    a0 := getNum8;
    WriteInt(a0());
    a0 := getNum7;
    WriteInt(a0());
    r0.i := 1;
    b0 := getPtr0;
    p0 := b0(r0);
    WriteInt(p0.i);
    b0 := getPtr1;
    p0 := b0(r0);
    WriteInt(p0.i);
    c0 := b0;
    p0 := c0(r0);
    WriteInt(p0.i)
  END Run;

BEGIN
  Run;
  WriteLn;
  a := getNum8;
  WriteInt(a());
  a := getNum7;
  WriteInt(a());
  r.i := 1;
  b := getPtr0;
  p := b(r);
  WriteInt(p.i);
  b := getPtr1;
  p := b(r);
  WriteInt(p.i);
  c := b;
  p := c(r);
  WriteInt(p.i);
  WriteLn
END TProcVariables0Ref.
