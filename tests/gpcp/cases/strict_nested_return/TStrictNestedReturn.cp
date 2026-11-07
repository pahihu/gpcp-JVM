(* Strict CP (report Ch. 6.5): a local procedure is not a procedure value,
   so it cannot be returned as a procedure-type result. *)
MODULE TStrictNestedReturn;
  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  PROCEDURE Make(): Hook;
    PROCEDURE Inner(x: INTEGER): INTEGER;
    BEGIN RETURN x + 1 END Inner;
  BEGIN
    RETURN Inner
  END Make;

BEGIN
  ASSERT(Make() # NIL)
END TStrictNestedReturn.