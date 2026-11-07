(*
 * Adapted from oberonc: tests/base/ProcComparisons.Mod
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
 *   - The four IF statements and their order are unchanged; target output is 1 2 3.
 *)

MODULE TProcComparisonsRef;
  IMPORT CPmain, Console;
  VAR x: BOOLEAN;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE P2(i: INTEGER): INTEGER;
  BEGIN RETURN 2 END P2;

  PROCEDURE P1(i: INTEGER): INTEGER;
  BEGIN RETURN 1 END P1;

BEGIN
  IF P2 = P1 THEN WriteInt(0) END;
  IF P2 = P2 THEN WriteInt(1) END;
  IF P2 # P1 THEN WriteInt(2) END;
  IF P2 # NIL THEN WriteInt(3) END;
  IF P2 = NIL THEN WriteInt(4) END;
  x := P2 = P2;
  x := P2 = NIL;
  Console.WriteLn()
END TProcComparisonsRef.
