(* ADR-042: a procedure-typed record field has a lazily built wrapper class. *)
MODULE TProcField;
  IMPORT CPmain, Console;
  TYPE R = RECORD hook: PROCEDURE (x: INTEGER): INTEGER END;
  VAR r: R;
  PROCEDURE Add1(x: INTEGER): INTEGER;
  BEGIN RETURN x + 1 END Add1;
BEGIN
  r.hook := Add1;
  IF r.hook(41) = 42 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TProcField.
