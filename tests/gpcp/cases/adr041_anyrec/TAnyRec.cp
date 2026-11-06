(* ADR-041: ANYREC is dynamically typed, so WITH over a VAR param works. *)
MODULE TAnyRec;
  IMPORT CPmain, Console;
  TYPE R = RECORD v: INTEGER END;
  VAR got: INTEGER; r: R;
  PROCEDURE P(VAR x: ANYREC);
  BEGIN
    WITH x: R DO got := x.v ELSE got := -1 END
  END P;
BEGIN
  r.v := 42;
  P(r);
  IF got = 42 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TAnyRec.
