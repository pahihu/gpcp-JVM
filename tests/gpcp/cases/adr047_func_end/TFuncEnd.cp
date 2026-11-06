(* ADR-047: a function falling through to END still returns a value. *)
MODULE TFuncEnd;
  IMPORT CPmain, Console;
  VAR n: INTEGER;
  PROCEDURE F(): INTEGER;
  BEGIN
    IF n = 0 THEN n := 1 END
  END F;
  PROCEDURE G(): INTEGER;
  BEGIN
    IF n = 2 THEN n := 3 END
  END G;
  PROCEDURE Run;
    VAR a, b: INTEGER;
  BEGIN
    n := 0; a := F();
    n := 2; b := G();
    IF (a = 0) & (b = 0) & (n = 3) THEN
      Console.WriteString("PASS")
    ELSE
      Console.WriteString("FAIL")
    END;
    Console.WriteLn()
  END Run;
BEGIN Run END TFuncEnd.
