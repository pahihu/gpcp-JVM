(* ADR-051: a CHAR literal works as a one-character string. *)
MODULE TCharStr;
  IMPORT CPmain, Console;
  VAR s: ARRAY 8 OF CHAR; ok: BOOLEAN;
  PROCEDURE P(IN x: ARRAY OF CHAR);
  BEGIN
  END P;
  PROCEDURE Run;
    VAR t: ARRAY 4 OF CHAR;
  BEGIN
    s := 'Q';
    t := 'Z';
    P('a');
    ok := (s[0] = "Q") & (s[1] = 0X) & (t[0] = "Z") & (t[1] = 0X) &
          ('A' + 'B' = "AB");
    IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
    Console.WriteLn()
  END Run;
BEGIN Run END TCharStr.
