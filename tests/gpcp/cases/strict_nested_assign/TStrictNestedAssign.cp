(* Strict CP (report Ch. 6.5): a procedure local to another procedure is
   not a procedure value and must be a compile error. *)
MODULE TStrictNestedAssign;
  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    f: Hook;

  PROCEDURE Outer;
    PROCEDURE Inner(x: INTEGER): INTEGER;
    BEGIN RETURN x + 1 END Inner;
  BEGIN
    f := Inner
  END Outer;

BEGIN
  Outer
END TStrictNestedAssign.