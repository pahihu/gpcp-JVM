(* ADR-043: a field of a private record may be exported without error 183. *)
MODULE TPrivField;
  IMPORT CPmain, Console;
  TYPE R = RECORD f*: INTEGER END;
  VAR r: R;
BEGIN
  r.f := 1;
  IF r.f = 1 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TPrivField.
