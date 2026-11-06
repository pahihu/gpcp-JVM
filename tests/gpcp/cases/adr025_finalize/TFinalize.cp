(* ADR-025: FINALIZE is predeclared on ANYPTR and needs no NEW marker. *)
MODULE TFinalize;
  IMPORT CPmain, Console;
  TYPE R = POINTER TO RECORD END;
  VAR r: R;
  PROCEDURE (r: R) FINALIZE;
  BEGIN
  END FINALIZE;
BEGIN
  NEW(r);
  IF r # NIL THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TFinalize.
