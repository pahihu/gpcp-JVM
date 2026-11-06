(* ADR-048: the type name is in scope while its own body is parsed. *)
MODULE TRecType;
  IMPORT CPmain, Console;
  TYPE Node = POINTER TO RECORD v: INTEGER; next: Node END;
  VAR n: Node;
BEGIN
  NEW(n); NEW(n.next); n.v := 1; n.next.v := 2;
  IF (n.v = 1) & (n.next.v = 2) THEN
    Console.WriteString("PASS")
  ELSE
    Console.WriteString("FAIL")
  END;
  Console.WriteLn()
END TRecType.
