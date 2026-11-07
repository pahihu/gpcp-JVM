(* Stage 2: a nested procedure that does not access enclosing locals has
   an empty captured environment; two values of that procedure are equal
   and remain callable after the enclosing function returns. *)
MODULE TNestedNoCapture;
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

  PROCEDURE Make(): Hook;
    PROCEDURE Inner(y: INTEGER): INTEGER;
    BEGIN RETURN 2*y END Inner;
  BEGIN RETURN Inner END Make;

BEGIN
  f := Make();
  g := Make();

  Check(f(3) = 6,                 "f-call");
  Check(g(4) = 8,                 "g-call");
  Check(f = g,                    "no-capture-eq");
  Check(~(f # g),                 "no-capture-neq")
END TNestedNoCapture.
