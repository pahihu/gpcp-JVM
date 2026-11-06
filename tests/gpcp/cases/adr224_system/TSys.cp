(* ADR-224: IMPORT SYSTEM is allowed on the JVM and SYSTEM.LSH/ROT exist. *)
MODULE TSys;
  IMPORT CPmain, Console, SYSTEM;
  VAR ok: BOOLEAN;
BEGIN
  ok := (SYSTEM.LSH(1, 4) = 16) & (SYSTEM.ROT(1, 1) = 2);
  IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TSys.
