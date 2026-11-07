(*
 * Adapted from oberonc: tests/base/UniqueTypeAndProcNames.Mod
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

MODULE UniqueTypeAndProcNames;
  IMPORT CPmain, Console;
  TYPE T = RECORD a: INTEGER END;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE P1(i: INTEGER);
    TYPE T = RECORD b: CHAR END;
    PROCEDURE P2(j: INTEGER);
      TYPE T2 = RECORD b: ARRAY 2, 2 OF CHAR END;
      PROCEDURE P3(j: INTEGER);
         VAR x: T2;
      BEGIN
        x.b[1][1] := "F";
        WriteChar(x.b[1][1])
      END P3;
    BEGIN
      WriteChar("E");
      P3(3)
    END P2;
  BEGIN
    WriteChar("D");
    P2(2)
  END P1;

  PROCEDURE P0(i: INTEGER);
    TYPE T = RECORD b: REAL END;
    PROCEDURE P2(j: INTEGER);
      TYPE T2 = RECORD b: ARRAY 3, 3 OF CHAR END;
      PROCEDURE P3(j: INTEGER);
         VAR x: T2;
      BEGIN
        x.b[2][2] := "C";
        WriteChar(x.b[2][2])
      END P3;
    BEGIN
      WriteChar("B");
      P3(3)
    END P2;
  BEGIN
    WriteChar("A");
    P2(2)
  END P0;

BEGIN
  P0(1); WriteLn; P1(1)
END UniqueTypeAndProcNames.