(* fixProcEqual: structural equality of procedure values on the JVM.
   Kotlin-style model (FunctionReference): two procedure values are equal
   when they denote the same procedure.  NIL keeps its usual meaning.
   Calls through procedure values must keep working. *)
MODULE TProcEqBasic;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    f, g: Hook;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Triple(x: INTEGER): INTEGER;
  BEGIN RETURN 3*x END Triple;

  PROCEDURE Apply(cb: Hook; x: INTEGER): INTEGER;
  BEGIN RETURN cb(x) END Apply;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  f := Double;
  g := Double;

  Check(f = g,                 "same-proc-two-vars");
  Check(f = Double,            "var-vs-literal");
  Check(Double = f,            "literal-vs-var");
  Check(Double = Double,       "literal-vs-literal");
  Check(~(f # g),              "not-equal-operator");
  Check(f = f,                 "self");

  Check(f(3) = 6,              "call-through-var");
  Check(Apply(Double, 2) = 4,  "call-through-param");
  Check(Apply(f, 4) = 8,       "call-var-through-param");

  g := Triple;
  Check(f # g,                 "different-procs");
  Check(~(f = g),              "different-procs-eq");

  g := f;
  Check(f = g,                 "copied-var");

  f := NIL;
  Check(f = NIL,               "nil-eq");
  Check(~(f # NIL),            "nil-neq");
  Check(NIL = f,               "nil-left");
  Check(NIL = NIL,             "nil-nil");

  f := Double;
  Check(f # NIL,               "nonnil-neq");
  Check(~(f = NIL),            "nonnil-eq")
END TProcEqBasic.
