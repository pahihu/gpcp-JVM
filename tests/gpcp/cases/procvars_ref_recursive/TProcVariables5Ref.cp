(*
 * Adapted from oberonc: tests/base/ProcVariables5.Mod
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
 *   - BEGIN added where Oberon-07 allows a bare RETURN body.
 *)

MODULE TProcVariables5Ref;
  IMPORT CPmain, Console;
  TYPE T = PROCEDURE (x, y: INTEGER; z: BYTE);
  VAR v: T; i, j: INTEGER;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 0) END WriteInt;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE P(x, y: INTEGER; z: BYTE);
  BEGIN WriteInt(x + y + z) END P;

  PROCEDURE P1(p: PROCEDURE (x, y: INTEGER; z: BYTE));
  BEGIN
    IF i = 0 THEN
      INC(i);
      v := p;
      p(1, 2, 3);
      v(1, 2, 4);
      P1(p);
      P1(v)
    END
  END P1;

  PROCEDURE P2(p: T);
  BEGIN
    IF j = 0 THEN
      INC(j);
      v := p;
      p(1, 2, 3);
      v(1, 2, 4);
      P1(p);
      P1(v);
      P2(p);
      P2(v)
    END
  END P2;

BEGIN
  i := 0; j := 0;
  v := P;
  P1(P);
  P2(P);
  WriteLn
END TProcVariables5Ref.
