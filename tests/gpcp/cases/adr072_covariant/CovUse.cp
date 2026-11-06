MODULE CovUse;
  IMPORT CPmain, Console, CovBase, CovChild;
  VAR c: CovChild.Child; b: CovBase.Base;
BEGIN
  NEW(c); b := c;
  IF b.New() # NIL THEN
    Console.WriteString("PASS")
  ELSE
    Console.WriteString("FAIL")
  END;
  Console.WriteLn()
END CovUse.
