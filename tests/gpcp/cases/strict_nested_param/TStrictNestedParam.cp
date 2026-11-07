(* Strict CP (report Ch. 6.5): a local procedure is not a procedure value,
   so it cannot be passed to a procedure-typed formal. *)
MODULE TStrictNestedParam;
  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  PROCEDURE Apply(cb: Hook; x: INTEGER): INTEGER;
  BEGIN RETURN cb(x) END Apply;

  PROCEDURE Outer;
    PROCEDURE Inner(x: INTEGER): INTEGER;
    BEGIN RETURN x + 1 END Inner;
  BEGIN
    ASSERT(Apply(Inner, 1) = 2)
  END Outer;

BEGIN
  Outer
END TStrictNestedParam.