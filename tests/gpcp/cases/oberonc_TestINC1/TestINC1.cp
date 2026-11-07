(*
 * Adapted from oberonc: tests/base/TestINC1.Mod
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

MODULE TestINC1;
  IMPORT CPmain, Console;
  VAR k: INTEGER;
      i: ARRAY 2 OF RECORD b : BYTE END;
      j: ARRAY 20 OF BYTE;
      x: BYTE;
  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE Effect(VAR x : BYTE) : INTEGER;
  BEGIN 
    WriteInt(x); (* 7 *)
    INC(k); 
    RETURN 0
  END Effect;

  PROCEDURE CallMe(VAR x : BYTE) : INTEGER;
  BEGIN
    RETURN x
  END CallMe;

  PROCEDURE P;
    VAR i: ARRAY 2 OF RECORD b : BYTE END;
        j: ARRAY 20 OF BYTE;
        x: BYTE;
  BEGIN 
    i[0].b := 6;
    x := 10;
    k := 0;
    j[x+5] := 7;
    INC(i[Effect(j[x+5])].b, 2);
    WriteInt(k); (* 1 *)
    WriteInt(i[0].b); (* 8 *)
    INC(i[0].b, j[x+5]);
    WriteInt(i[0].b); (* 15 *)
    INC(j[x+5], i[0].b);
    WriteInt(j[x+5]); (* 22 *)
    INC(x, CallMe(i[0].b));
    WriteInt(x); (* 25 *)
  END P; 
  
BEGIN
  P;
  WriteLn;
  i[0].b := 6;
  x := 10;
  k := 0;
  j[x+5] := 7;
  INC(i[Effect(j[x+5])].b, 2);
  WriteInt(k); (* 1 *)
  WriteInt(i[0].b); (* 8 *)
  INC(i[0].b, j[x+5]);
  WriteInt(i[0].b); (* 15 *)
  INC(j[x+5], i[0].b);
  WriteInt(j[x+5]); (* 22 *)
  INC(x, CallMe(i[0].b));
  WriteInt(x) (* 25 *)
END TestINC1.