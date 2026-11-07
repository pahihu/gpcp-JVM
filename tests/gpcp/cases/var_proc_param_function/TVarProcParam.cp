(* Valid CP: a function with VAR/OUT procedure parameters.  The explicit
   function result uses the JVM return slot, so procedure parameters must be
   boxed. *)
MODULE TVarProcParam;
  IMPORT CPmain, Console;

  TYPE
    P  = PROCEDURE (x: INTEGER): INTEGER;
    F1 = PROCEDURE (VAR y: P): INTEGER;
    F2 = PROCEDURE (VAR a: P; VAR b: P): INTEGER;
    FO = PROCEDURE (OUT y: P): INTEGER;

  VAR
    f1: F1;
    f2: F2;
    fo: FO;
    a, b: P;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Triple(x: INTEGER): INTEGER;
  BEGIN RETURN 3*x END Triple;

  PROCEDURE Call1(VAR y: P): INTEGER;
  BEGIN RETURN y(4) END Call1;

  PROCEDURE Call2(VAR x: P; VAR y: P): INTEGER;
  BEGIN y := x; RETURN x(5) END Call2;

  PROCEDURE Make(OUT y: P): INTEGER;
  BEGIN y := Double; RETURN 7 END Make;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  a := Double;
  b := Triple;

  f1 := Call1;
  Check(f1(a) = 8,              "one-var-proc-param");

  f2 := Call2;
  Check(f2(a, b) = 10,          "two-var-proc-param-result");
  Check(b(2) = 4,               "second-var-proc-param-assigned");
  Check(b = a,                  "second-var-proc-param-equality");

  b := Triple;
  fo := Make;
  Check(Make(b) = 7,            "out-proc-param-result");
  Check(b = a,                  "out-proc-param-assigned")
END TVarProcParam.
