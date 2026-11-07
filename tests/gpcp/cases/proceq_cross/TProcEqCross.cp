(* fixProcEqual: values produced in one module must compare structurally
   with values of the same procedure produced elsewhere.  Two procedures
   with the same name and signature but different owners are not equal. *)
MODULE TProcEqCross;
  IMPORT CPmain, Console, TProcEqLib;

  VAR
    f, g: TProcEqLib.Hook;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  f := TProcEqLib.Shared;
  g := TProcEqLib.GetDouble();
  Check(f = g,                       "lib-shared-vs-getter");
  Check(g = TProcEqLib.GetDouble(),  "two-getter-calls");
  Check(f = TProcEqLib.GetDouble(),  "shared-vs-getter");

  TProcEqLib.Store(Double);
  Check(TProcEqLib.Get() = Double,   "lib-stored-vs-fresh-literal");
  Check(Double = TProcEqLib.Get(),   "fresh-literal-vs-lib-stored");
  Check(TProcEqLib.Same(TProcEqLib.Get(), Double),
                                     "lib-compare-stored-vs-literal");
  Check(TProcEqLib.Same(TProcEqLib.Get(), TProcEqLib.Get()),
                                     "lib-compare-stored-vs-stored");

  Check(~TProcEqLib.Same(TProcEqLib.GetDouble(), Double),
                                     "same-name-different-owner");

  TProcEqLib.Store(NIL);
  Check(TProcEqLib.Get() = NIL,      "lib-stored-nil");
  Check(~TProcEqLib.Same(TProcEqLib.Get(), Double),
                                     "lib-compare-nil-vs-literal")
END TProcEqCross.
