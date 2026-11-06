(* ADR-027: ANYPTR locals and IN parameters get a real JVM frame type. *)
MODULE TAnyPtr;
  IMPORT CPmain, Console;
  PROCEDURE P(IN x: ANYPTR);
  BEGIN
  END P;
  PROCEDURE Run;
    VAR p: ANYPTR; ok: BOOLEAN;
  BEGIN
    ok := (p = NIL);
    P(p);
    IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
    Console.WriteLn()
  END Run;
BEGIN Run END TAnyPtr.
