(*
 * Adapted from oberonc: tests/base/TestEqualSignature00.Mod
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
 *   - A is declared EXTENSIBLE because Component Pascal requires it for B = RECORD(A).
 *)

MODULE TEqualSignature00Ref;
  IMPORT CPmain, Console;
  TYPE
    A = EXTENSIBLE RECORD i: INTEGER END;
    B = RECORD(A) k: CHAR END;
    P0 = PROCEDURE(x: ARRAY OF B);
    P1 = PROCEDURE(x: B);
    PTRB = POINTER TO B;
    P2 = PROCEDURE(x: PTRB);
    ARR = ARRAY 10 OF B;
    P3 = PROCEDURE(x: BYTE; y: CHAR; z: ARRAY OF B): CHAR;
    P4 = PROCEDURE(z: ARR; x: PROCEDURE(z: ARR): CHAR): CHAR;
  VAR
    p0: P0;
    p1: P1;
    p2: P2;
    p3: P3;
    p4: P4;
    x: ARRAY 1 OF B;
    pb: PTRB;
    y: ARR;

  PROCEDURE H0(x: ARRAY OF B);
  BEGIN Console.Write(x[0].k) END H0;

  PROCEDURE H1(x: B);
  BEGIN Console.Write(x.k) END H1;

  PROCEDURE H2(x: PTRB);
  BEGIN Console.Write(x.k) END H2;

  PROCEDURE H3(x: BYTE; y: CHAR; z: ARRAY OF B): CHAR;
  BEGIN RETURN CHR(x + ORD(y) + z[0].i) END H3;

  PROCEDURE H4(z: ARR; x: PROCEDURE(z: ARR): CHAR): CHAR;
  BEGIN RETURN x(z) END H4;

  PROCEDURE H5(): CHAR;
  BEGIN RETURN "F" END H5;

  PROCEDURE L(u: ARR): CHAR;
  BEGIN RETURN u[0].k END L;

BEGIN
  p0 := H0;
  x[0].k := "A";
  p0(x);
  p1 := H1;
  x[0].k := "B";
  p1(x[0]);
  p2 := H2;
  NEW(pb);
  pb.k := "C";
  p2(pb);
  p3 := H3;
  x[0].i := 2;
  Console.Write(p3(1, "A", x));
  p4 := H4;
  y[0].k := "E";
  Console.Write(p4(y, L));
  Console.Write(H5());
  Console.WriteLn()
END TEqualSignature00Ref.
