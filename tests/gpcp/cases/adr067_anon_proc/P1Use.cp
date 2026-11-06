MODULE P1Use;
  IMPORT CPmain, Console, P1Lib;
  VAR h: PROCEDURE (x: INTEGER): INTEGER;
BEGIN
  h := P1Lib.hook;
  IF h(41) = 42 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END P1Use.
