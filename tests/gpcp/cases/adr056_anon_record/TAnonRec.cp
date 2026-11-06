(* ADR-056: an anonymous record bound to an id-less pointer gets an id. *)
MODULE TAnonRec;
  IMPORT CPmain, Console;
  TYPE P = POINTER TO RECORD v: INTEGER END;
  VAR p: P;
BEGIN
  NEW(p); p.v := 7;
  IF p.v = 7 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TAnonRec.
