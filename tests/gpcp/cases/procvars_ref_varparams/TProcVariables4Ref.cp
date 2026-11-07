(*
 * Adapted from oberonc: tests/base/ProcVariables4.Mod
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
 *   - Oberon-07 WriteInt/WriteLn replaced by Console output.
 *   - Oberon-07 FLOOR replaced by SHORT(ENTIER(x)).
 *   - BEGIN added where Oberon-07 allows a bare RETURN body.
 *)

MODULE TProcVariables4Ref;
  IMPORT CPmain, Console;
  TYPE P0 = PROCEDURE (VAR x: REAL): INTEGER;
       P1 = PROCEDURE (VAR x: REAL; VAR y: P0): INTEGER;
       P2 = PROCEDURE (VAR x: REAL; y: PROCEDURE (VAR x: REAL): INTEGER): INTEGER;
       P3 = PROCEDURE (VAR x: REAL; VAR y: PROCEDURE (VAR x: REAL): INTEGER): INTEGER;
  VAR v: P0; v1: P1; v2: P2; v3: P3; f: REAL;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 0) END WriteInt;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE Floor(VAR x: REAL): INTEGER;
  BEGIN RETURN SHORT(ENTIER(x)) END Floor;

  PROCEDURE Floor1(VAR x: REAL; VAR y: P0): INTEGER;
  BEGIN RETURN y(x) END Floor1;

  PROCEDURE Floor2(VAR x: REAL; y: PROCEDURE (VAR x: REAL): INTEGER): INTEGER;
  BEGIN RETURN y(x) END Floor2;

  PROCEDURE Floor3(VAR x: REAL; VAR y: PROCEDURE (VAR x: REAL): INTEGER): INTEGER;
  BEGIN RETURN y(x) END Floor3;

BEGIN
  f := 8.5;
  v := Floor;
  WriteInt(v(f));
  f := 9.5;
  v1 := Floor1;
  WriteInt(v1(f, v));
  f := 10.5;
  v2 := Floor2;
  WriteInt(v2(f, v));
  v3 := Floor3;
  WriteLn
END TProcVariables4Ref.
