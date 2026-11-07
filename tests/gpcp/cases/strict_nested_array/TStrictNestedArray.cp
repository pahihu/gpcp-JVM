(* Strict CP: a local procedure is not a procedure value, including when it
   is assigned to a procedure-typed array element. *)
MODULE TStrictNestedArray;
  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    a: ARRAY 2 OF Hook;

  PROCEDURE Outer;
    PROCEDURE Inner(x: INTEGER): INTEGER;
    BEGIN RETURN x + 1 END Inner;
  BEGIN
    a[0] := Inner
  END Outer;

BEGIN
  Outer
END TStrictNestedArray.