(*
 * Adapted from oberonc: tests/base/CaseNum0.Mod
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

MODULE CaseNum0;
  IMPORT CPmain, Console;
  VAR i, a : INTEGER;
  
  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE P(i : INTEGER);
     VAR a : INTEGER;
  BEGIN
    CASE i OF
      8..10, 14:
        a := 1; 
      |2..4, 15..20, 25:
        a := 2; 
      |5..6:
        a := 3; 
    END;
    WriteInt(a)
  END P;

  PROCEDURE P1;
   VAR i: INTEGER;
  BEGIN
      i := 8;
      CASE i OF
       0..255: WriteInt(8)
      END;
      i := 0;
      CASE i OF
       -255..0: WriteInt(9)
      END
  END P1;

  PROCEDURE P2;
   VAR i: INTEGER;
  BEGIN
      i := -1;
      CASE i OF
       -1: WriteInt(-1)
       | 0: WriteInt(0)
       | +1: WriteInt(1)
      END
  END P2;

BEGIN
  i := 2;
  CASE i OF
    8..10, 14:
      a := 1; 
    |2..4, 15..20, 25:
      a := 2; 
    |5..6:
      a := 3; 
  END;
  WriteInt(a); (* 2 *)
  P(9); (* 1 *)
  P(4); (* 2 *)
  P(6); (* 3 *)
  P2; (* -1 *)
  P1 (* 8 9 *)
END CaseNum0.