(*
 * Adapted from oberonc: tests/base/Strings2.Mod
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

MODULE Strings2;
  IMPORT CPmain, Console;

CONST
  a = "a";
  abcd = "abcd";

VAR
  s4: ARRAY 4 OF CHAR;
  s5: ARRAY 5 OF CHAR;
  f: ARRAY 20 OF CHAR;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE P(x: ARRAY OF CHAR);
    VAR i : INTEGER;
  BEGIN
    FOR i := 0 TO LEN(x)-1 DO
      IF x[i] = 0X THEN
        WriteChar("$")
      ELSE
        WriteChar(x[i])
      END;
    END;
    WriteLn
  END P;

  PROCEDURE K;
   VAR f: ARRAY 20 OF CHAR;
  BEGIN
    f := "Hello";
    IF f = "" THEN WriteInt(1) END;
    f := "";
    IF f = "" THEN WriteInt(2) END;
    f[0] := 0X;
    IF f = "" THEN WriteInt(3) END
  END K;
BEGIN
  s4 := a; P(s4);
  s4 := "a"; P(s4);
  s4 := "ab"; P(s4);
  P(a);
  P("a");
  P("ab");
  (* s4 := abcd;  String too long *)
  (*s4 := "abcd"; String too long *)
  s5 := abcd; P(s5);
  s5 := "abcd"; P(s5);
  s5 := ""; P(s5);
  f := "Hello";
  IF f = "" THEN WriteInt(1) END;
  f := "";
  IF f = "" THEN WriteInt(2) END;
  f[0] := 0X;
  IF f = "" THEN WriteInt(3) END;
  K
END Strings2.