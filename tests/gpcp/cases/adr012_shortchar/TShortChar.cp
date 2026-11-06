(* ADR-012: ARRAY OF SHORTCHAR must be allocated as char[], not short[]. *)
MODULE TShortChar;
  IMPORT CPmain, Console;
  TYPE Buf = ARRAY 4 OF SHORTCHAR;
  VAR g: Buf;
  PROCEDURE Fill(VAR x: ARRAY OF SHORTCHAR; OUT n: INTEGER);
    VAR i: INTEGER;
  BEGIN
    n := LEN(x);
    FOR i := 0 TO LEN(x) - 1 DO x[i] := SHORT(CHR(ORD("A") + i)) END
  END Fill;
  PROCEDURE Run;
    VAR l: Buf; n: INTEGER;
  BEGIN
    Fill(l, n);
    g[0] := 41X; g[1] := 42X;
    IF (n = 4) & (l[0] = 41X) & (l[3] = 44X) &
       (g[0] = 41X) & (g[1] = 42X) THEN
      Console.WriteString("PASS")
    ELSE
      Console.WriteString("FAIL")
    END;
    Console.WriteLn()
  END Run;
BEGIN Run END TShortChar.
