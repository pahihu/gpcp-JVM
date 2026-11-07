(* Stage 2: a nested procedure value captures the activation record of
   its enclosing procedure.  The value must remain callable after the
   enclosing procedure has returned, and two values created in the same
   activation must compare equal. *)
MODULE TNestedCapture;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (y: INTEGER): INTEGER;

  VAR
    f, g: Hook;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

  PROCEDURE Outer;
    VAR
      x: INTEGER;

    PROCEDURE Inner(y: INTEGER): INTEGER;
    BEGIN RETURN x + y END Inner;

  BEGIN
    x := 10;
    f := Inner;
    g := Inner;
    Check(f = g,                  "same-activation-eq");
    Check(~(f # g),               "same-activation-neq");
    Check(f(5) = 15,              "call-inside");
    Check(Inner = Inner,          "two-literals-eq")
  END Outer;

BEGIN
  Outer;
  Check(f(7) = 17,                "call-after-return");
  Check(f = g,                    "values-after-return");
  Check(f # NIL,                  "escaped-nonnil")
END TNestedCapture.
