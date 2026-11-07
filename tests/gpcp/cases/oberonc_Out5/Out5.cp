(*
 * Adapted from oberonc: tests/base/Out5.Mod
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

MODULE Out5;
  IMPORT CPmain, Console;
  TYPE A = RECORD x : INTEGER END;
  VAR i: INTEGER;
      v : ARRAY 20 OF INTEGER;
      a : A;
  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

BEGIN 
  i := 1;
  v[i] := 10;
  WriteInt(v[i]);
  i := v[i] + 1; 
  WriteInt(i);
  v[i] := i + 1; 
  WriteInt(v[i]);
  i := v[i] + v[i] - 4; 
  WriteInt(i);
  a.x := 21;
  WriteInt(a.x);
  i := a.x + 1; 
  WriteInt(i);
  a.x := i + 1; 
  WriteInt(a.x);
  i := a.x + a.x - 22; 
  WriteInt(i);
END Out5.