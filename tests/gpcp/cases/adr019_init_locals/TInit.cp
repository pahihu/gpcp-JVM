(* ADR-019: scalar locals are initialized by the JVM back end. *)
MODULE TInit;
  IMPORT CPmain, Console;
  TYPE P = POINTER TO RECORD x: INTEGER END;
       Proc = PROCEDURE;
  PROCEDURE Run;
    VAR i: INTEGER; l: LONGINT; r: REAL; sr: SHORTREAL;
        p: P; pr: Proc; ok: BOOLEAN;
  BEGIN
    ok := (i = 0) & (l = 0) & (r = 0.0) & (sr = 0.0) &
          (p = NIL) & (pr = NIL);
    IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
    Console.WriteLn()
  END Run;
BEGIN Run END TInit.
