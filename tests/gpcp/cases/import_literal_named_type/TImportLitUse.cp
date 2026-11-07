(* Stage 3: an imported procedure literal must get the correct JVM method
   descriptor and share the host class of the named exported procedure type.
   Regression for the former `Field ... illegal signature` /
   `ClassFormatError` on the JVM backend. *)
MODULE TImportLitUse;
  IMPORT CPmain, Console, TImportLitLib;

  VAR
    f, g: TImportLitLib.Hook;
    h: PROCEDURE (x: INTEGER): INTEGER;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  f := TImportLitLib.Double;
  Check(f(3) = 6,                         "call-imported-literal");

  g := TImportLitLib.Shared;
  Check(f = g,                            "literal-vs-lib-value");
  Check(TImportLitLib.Double = g,         "imported-literal-left");
  Check(g = TImportLitLib.Double,         "imported-literal-right");
  Check(TImportLitLib.Double = TImportLitLib.Double,
                                          "two-imported-literals");
  Check(TImportLitLib.GetDouble() = f,    "getter-vs-literal");

  h := TImportLitLib.Double;
  Check(h(4) = 8,                         "anonymous-type-call");
  Check(h = f,                            "anonymous-vs-named");

  f := NIL;
  Check(f # TImportLitLib.Double,         "nil-vs-imported-literal")
END TImportLitUse.
