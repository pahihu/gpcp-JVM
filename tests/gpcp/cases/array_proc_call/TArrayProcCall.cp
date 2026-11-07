(* Valid Component Pascal: a procedure value taken from an array element
   can be called directly.  This used to trap in ExprDesc.liveActuals. *)
MODULE TArrayProcCall;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    a: ARRAY 3 OF Hook;
    i: INTEGER;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Triple(x: INTEGER): INTEGER;
  BEGIN RETURN 3*x END Triple;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

  PROCEDURE Run;
    VAR
      b: ARRAY 2 OF Hook;
  BEGIN
    b[0] := Triple;
    b[1] := Double;
    Check(b[0](3) = 9,       "local-array-literal-index");
    i := 1;
    Check(b[i](4) = 8,       "local-array-var-index")
  END Run;

  PROCEDURE Apply(a: ARRAY OF Hook; i: INTEGER; x: INTEGER): INTEGER;
  BEGIN RETURN a[i](x) END Apply;

BEGIN
  a[0] := Double;
  a[1] := Triple;
  a[2] := Double;

  Check(a[0](3) = 6,         "global-array-literal-index");
  i := 1;
  Check(a[i](3) = 9,         "global-array-var-index");
  i := 2;
  Check(a[i](4) = 8,         "global-array-var-index-2");
  Check(a[0](1) + a[1](1) = 5, "two-element-calls");

  Run;

  Check(Apply(a, 0, 5) = 10, "open-array-parameter")
END TArrayProcCall.
