(* ADR-028/039: every boxed OUT parameter proxy is initialized. *)
MODULE TOut;
  IMPORT CPmain, Console;
  VAR a, r: INTEGER; b: LONGINT; c: REAL; d: SET;
  PROCEDURE P(OUT a: INTEGER; OUT b: LONGINT; OUT c: REAL; OUT d: SET);
  BEGIN
    a := 1; b := 2; c := 3.0; d := {1}
  END P;
  PROCEDURE F(OUT a: INTEGER; OUT b: LONGINT): INTEGER;
  BEGIN
    a := 7; b := 8; RETURN 9
  END F;
BEGIN
  P(a, b, c, d);
  r := F(a, b);
  IF (a = 7) & (b = 8) & (r = 9) & (c = 3.0) & (d = {1}) THEN
    Console.WriteString("PASS")
  ELSE
    Console.WriteString("FAIL")
  END;
  Console.WriteLn()
END TOut.
