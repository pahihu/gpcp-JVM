(* ADR-052: U+00A0 (NBSP) is whitespace for the scanner. *)
MODULE TNbsp;
  IMPORT CPmain, Console;
  VAR x: INTEGER;
BEGIN
  x := 42;
  IF x = 42 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TNbsp.
