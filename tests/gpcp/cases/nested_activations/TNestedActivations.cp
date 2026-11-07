(* Stage 2: values of the same nested procedure from different
   activations have different captured environments and must not compare
   equal.  Copies of one value remain equal. *)
MODULE TNestedActivations;
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

  PROCEDURE Make(n: INTEGER): Hook;
    PROCEDURE Inner(y: INTEGER): INTEGER;
    BEGIN RETURN n + y END Inner;
  BEGIN RETURN Inner END Make;

BEGIN
  f := Make(1);
  g := Make(2);

  Check(f # g,                    "different-activations-neq");
  Check(~(f = g),                 "different-activations-eq");
  Check(f(10) = 11,               "f-call");
  Check(g(10) = 12,               "g-call");

  g := f;
  Check(f = g,                    "copied");

  Check(~(Make(1) = Make(1)),     "two-makes-neq")
END TNestedActivations.
