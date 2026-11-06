MODULE WUse3;
  IMPORT CPmain, Console, WLibB;
  TYPE WLibA = INTEGER;
  VAR x: WLibA;
BEGIN
  x := 1;
  IF x = 1 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END WUse3.
