(* ADR-049: string literal is compatible with an IN parameter by value. *)
MODULE TInParam;
  IMPORT CPmain, Console;
  TYPE S = ARRAY 4 OF CHAR;
  VAR ok: BOOLEAN;
  PROCEDURE P(IN s: S);
  BEGIN
    ok := (s[0] = "a") & (s[1] = "b") & (s[2] = "c") & (s[3] = 0X)
  END P;
BEGIN
  P("abc");
  IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TInParam.
