(*
 * Adapted from oberonc: tests/base/TestFor.Mod
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

MODULE TestFor;
  IMPORT CPmain, Console;
  CONST minus1 = -1;
  TYPE R0 = RECORD x, y : INTEGER END;
       ARR = ARRAY 5 OF INTEGER;
  VAR  i, x: INTEGER;
       r0 : R0;
       v : ARR;
  
  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE P3(VAR v3 : ARR);
  BEGIN
    v3[0] := 1; 
    r0.x := 4;
    FOR i := r0.x + 3 TO r0.x + 3 + v3[0] + v3[0] DO
      WriteInt(i) 
    END;
  END P3;
  
  PROCEDURE P2(VAR k : INTEGER);
  BEGIN
    v[0] := 1; 
    r0.x := 4;
    FOR k := r0.x + 3 TO r0.x + 3 + v[0] + v[0] DO
      WriteInt(k) 
    END;
  END P2;
  
  PROCEDURE P1(j : INTEGER);
  VAR  i1: INTEGER;
       r1 : R0;
       v1 : ARRAY 5 OF INTEGER;
  BEGIN
   FOR i1 := 0 TO 2 BY 1 DO
      WriteInt(i1) 
    END;
    x := 3;
    FOR i1 := x TO 5 DO
      WriteInt(i1)
    END;
    j := 8;
    FOR i1 := 6 TO j DO
      WriteInt(i1)
    END;
    FOR i1 := j TO 0 BY minus1 DO
      WriteInt(i1)
    END;
    WriteLn;
    r1.x := 0;
    FOR i1 := r1.x TO 2 DO
      WriteInt(i1) 
    END;
    r1.x := 2;
    FOR i1 := 3 TO r1.x + 3 DO
      WriteInt(i1) 
    END;
    WriteLn;
    v1[0] := 1; 
    r1.x := 4;
    FOR i1 := r1.x + 3 TO r1.x + 3 + v1[0] + v1[0] DO
      WriteInt(i1) 
    END;
  END P1;
BEGIN
  FOR i := 0 TO 2 BY 1 DO
    WriteInt(i) 
  END;
  x := 3;
  FOR i := x TO 5 DO
    WriteInt(i)
  END;
  x := 8;
  FOR i := 6 TO x DO
    WriteInt(i)
  END;
  FOR i := x TO 0 BY minus1 DO
    WriteInt(i)
  END;
  WriteLn;
  r0.x := 0;
  FOR i := r0.x TO 2 DO
    WriteInt(i) 
  END;
  r0.x := 2;
  FOR i := 3 TO r0.x + 3 DO
    WriteInt(i) 
  END;
  WriteLn;
  v[0] := 1; 
  r0.x := 4;
  FOR i := r0.x + 3 TO r0.x + 3 + v[0] + v[0] DO
    WriteInt(i) 
  END;
  WriteLn;
  P1(0);
  i := 0;
  WriteLn;
  P2(i);
  WriteLn;
  P3(v);
  WriteLn;
END TestFor.