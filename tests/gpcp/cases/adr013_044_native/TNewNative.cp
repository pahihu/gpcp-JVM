(* ADR-013: NEW on an extension of a native (SYSTEM MODULE) record type. *)
MODULE TNewNative;
  IMPORT CPmain, Console, NativeLib;
  TYPE P = POINTER TO RECORD (NativeLib.Extensible) z: INTEGER END;
  VAR p: P;
BEGIN
  NEW(p); p.y := 1; p.z := 2;
  IF (p.y = 1) & (p.z = 2) THEN
    Console.WriteString("PASS")
  ELSE
    Console.WriteString("FAIL")
  END;
  Console.WriteLn()
END TNewNative.
