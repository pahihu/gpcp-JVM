(* fixProcEqual: procedure types with matching formal parameter lists are
   equal types (CP report, Appendix A), even when they are denoted by
   different type identifiers.  Values of both types must compare equal. *)
MODULE TProcEqNamedTypes;
  IMPORT CPmain, Console;

  TYPE
    H1 = PROCEDURE (x: INTEGER): INTEGER;
    H2 = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    a: H1;
    b: H2;
    f: H1;

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
  a := Double;
  b := Double;
  f := Double;

  Check(a = b,             "h1-vs-h2-same-proc");
  Check(~(a # b),          "h1-vs-h2-neq");
  Check(a = f,             "h1-vs-h1");
  Check(b = f,             "h2-vs-h1");

  b := NIL;
  Check(a # b,             "nonnil-vs-nil");
  Check(~(a = b),          "nonnil-vs-nil-eq");

  b := Double;
  Check(a = b,             "h1-vs-h2-after-nil")
END TProcEqNamedTypes.
