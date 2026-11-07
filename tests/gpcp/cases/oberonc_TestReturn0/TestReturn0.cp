(*
 * Adapted from oberonc: tests/base/TestReturn0.Mod
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
 *   - Oberon-07 WriteInt/WriteLn replaced by Console output.
 *   - BEGIN added for the bare RETURN bodies of P2 and P3.
 *)

MODULE TestReturn0;
  IMPORT CPmain, Console;
  VAR x: INTEGER;

  PROCEDURE WriteInt(x: INTEGER);
  BEGIN Console.WriteInt(x, 4) END WriteInt;

  PROCEDURE P1(): INTEGER;
  BEGIN RETURN x
  END P1;

  PROCEDURE P2(): INTEGER;
  BEGIN RETURN x
  END P2;

  PROCEDURE P3(): INTEGER;
  VAR dummy: INTEGER;
  BEGIN RETURN x+dummy
  END P3;
BEGIN
  x := 1;
  WriteInt(P1());
  WriteInt(P2());
  WriteInt(P3())
END TestReturn0.
