(*
 * Adapted from oberonc: tests/base/TestFor1.Mod
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

MODULE TestFor1;
  IMPORT CPmain, Console;
  VAR v, beg, end : INTEGER;
  
  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE WriteChar(c: CHAR);
  BEGIN Console.Write(c) END WriteChar;

  PROCEDURE WriteString(IN s: ARRAY OF CHAR);
  BEGIN Console.WriteString(s) END WriteString;

  PROCEDURE WriteLn;
  BEGIN Console.WriteLn() END WriteLn;

  PROCEDURE For0;
    VAR v, beg, end : INTEGER;
  BEGIN
    beg := 3;
    end := 10;
    FOR v := beg TO end BY 2 DO WriteInt(v) END;
    WriteLn
  END For0;
  
  PROCEDURE For1;
  BEGIN
    beg := 0;
    end := 3;
    FOR v := beg TO end DO WriteInt(v) END;
    WriteLn
  END For1;
  
  PROCEDURE For2(VAR v1, beg1, end1 : INTEGER; v0, beg0, end0 : INTEGER );
  BEGIN
    FOR v1 := beg1 TO end1 BY 2 DO WriteInt(v1) END;
    WriteLn;
    FOR v0 := beg0 TO end0 DO WriteInt(v0) END;
    WriteLn;
    FOR v1 := beg TO end0 DO WriteInt(v1) END;
    WriteLn
  END For2;
  PROCEDURE For4;
  BEGIN
    beg := 10;
    end := 3;
    FOR v := beg TO end BY -1 DO WriteInt(v) END;
    WriteLn
  END For4;
BEGIN
  For0; For1; For2(v, beg, end, 0, 3, 10); For4
END TestFor1.