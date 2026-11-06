(* ADR-044: a native interface record stays copyable (no error 152). *)
MODULE TCopyNative;
  IMPORT CPmain, Console, NativeLib;
  VAR a, b: NativeLib.Copyable;
BEGIN
  a.x := 5; b := a;
  IF b.x = 5 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TCopyNative.
