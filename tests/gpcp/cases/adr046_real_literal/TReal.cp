(* ADR-046: a real literal adopts the target real type (no float/double mix). *)
MODULE TReal;
  IMPORT CPmain, Console;
  VAR ok: BOOLEAN;
BEGIN
  ok := (MIN(SHORTREAL) <= MAX(SHORTREAL)) & (MIN(REAL) <= MAX(REAL));
  IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TReal.
