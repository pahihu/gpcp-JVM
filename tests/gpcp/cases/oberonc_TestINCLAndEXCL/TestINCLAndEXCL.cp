(*
 * Adapted from oberonc: tests/base/TestINCLAndEXCL.Mod
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

MODULE TestINCLAndEXCL;
  IMPORT CPmain, Console;
  CONST K = {1, 2, 3};
  VAR y : SET;
      j,f : INTEGER;
      b : ARRAY 2 OF SET;
      r: RECORD a: ARRAY 2 OF RECORD b: INTEGER END END;
   
  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE PrintSet(x : SET);
  VAR i : INTEGER;
  BEGIN
    FOR i:= 0 TO 31 DO
      IF i IN x THEN WriteInt(i) END
    END;
    WriteLn
  END PrintSet;

  PROCEDURE P0(a0 : SET; VAR a1 : ARRAY OF SET);
    VAR i : ARRAY 2 OF SET;
        z : RECORD x : SET END;
        x : BYTE;
  BEGIN 
    x := 0;
    i[0] := K; 
    i[1] := K + {8}; 
    INCL(i[0], 8);
    PrintSet(i[0]); (* {1 2 3 8} *)
    EXCL(i[x+1], 1);
    PrintSet(i[x+1]); (* {2 3 8} *)
    
    z.x := K;
    EXCL(z.x, 2);
    PrintSet(z.x); (* {1 3} *)
        
    EXCL(a0, 2);
    PrintSet(a0); (* {1 3} *)
    
    EXCL(a1[x+1], 3);
    PrintSet(a1[x+1]); (* {1 2} *)
    
    j := 0;
    INCL(a1[j+1], 3);
    PrintSet(a1[j+1]); (* {1 2 3} *)
    INCL(a0, 8+x);
    PrintSet(a0); (* {1 3 8} *)
  END P0; 
  
  PROCEDURE Effect(VAR x : BYTE) : INTEGER;
  BEGIN 
    WriteInt(x); (* 7 *)
    INC(f); 
    RETURN 0
  END Effect;
  
  PROCEDURE P1;
    VAR i : ARRAY 2 OF RECORD b : SET END;
        j : ARRAY 20 OF BYTE;
        z : ARRAY 20 OF BYTE;
        x : BYTE;
  BEGIN 
    i[0].b := K;
    x := 10;
    f := 0;
    j[x+5] := 7;
    EXCL(i[Effect(j[x+5])].b, 2);
    WriteInt(f); (* 1 *)
    PrintSet(i[0].b); (* {1 3} *)
    z[x+1] := 8;
    INCL(i[Effect(j[x+5])].b, z[x+1]);
    WriteInt(f); (* 2 *)
    PrintSet(i[0].b); (* {1 3 8} *)
    z[2+x] := 10;
    INCL(i[Effect(j[x+5])].b, z[x+1] + z[2+x]);
    WriteInt(f); (* 3 *)
    PrintSet(i[0].b); (* {1 3 8 18} *)
  END P1; 


  PROCEDURE P2(VAR a0 : SET);
    VAR x : BYTE;
  BEGIN
    x := 1;
    INCL(a0, 8+x);
    PrintSet(a0); (* {2 9} *)
  END P2;

BEGIN
  y := K;
  EXCL(y, 2); (* {1 3} *)
  PrintSet(y);
  y := K;
  j := 1;
  r.a[-1+j].b := 2;
  EXCL(y, r.a[-1+j].b); (* {1 3} *)
  PrintSet(y);
  j := 2;
  y := K;
  EXCL(y, j);
  PrintSet(y); (* {1 3} *)
  b[j - 1] := K;
  EXCL(b[j - 1], j); (* {1 3} *)
  PrintSet(b[j - 1]);
  y := K;
  b[1] := K;
  P0(y, b);
  P1;
  y := {2};
  P2(y)
END TestINCLAndEXCL.