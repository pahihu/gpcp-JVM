MODULE WUse;
  IMPORT CPmain, Console, WLibB;
  VAR t: WLibB.T;
BEGIN
  t := WLibB.Get();
  IF t.v = 42 THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END WUse.
