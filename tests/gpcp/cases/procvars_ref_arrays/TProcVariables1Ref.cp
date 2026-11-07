(*
 * Adapted from oberonc: tests/base/ProcVariables1.Mod
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
 *)

MODULE TProcVariables1Ref;
  IMPORT CPmain, Console;
  TYPE
    R = RECORD i: INTEGER END;
    MyFun = PROCEDURE(r: R): INTEGER;
  VAR
    a: ARRAY 2 OF MyFun;
    i: INTEGER;
    r: R;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE F1(x: R): INTEGER;
  BEGIN RETURN x.i + 1 END F1;

  PROCEDURE F2(x: R): INTEGER;
  BEGIN RETURN x.i + 2 END F2;

  PROCEDURE Run;
    VAR a0: ARRAY 2 OF MyFun;
  BEGIN
    r.i := 1;
    a0[0] := F1;
    a0[1] := F2;
    FOR i := 0 TO 1 DO WriteInt(a0[i](r)) END
  END Run;

BEGIN
  Run;
  WriteLn;
  r.i := 1;
  a[0] := F1;
  a[1] := F2;
  FOR i := 0 TO 1 DO WriteInt(a[i](r)) END;
  WriteLn
END TProcVariables1Ref.
