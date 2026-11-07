(* Strict CP (report Ch. 6.5): a local procedure is not a procedure value,
   so it cannot appear in a procedure-type comparison. *)
MODULE TStrictNestedCompare;
  PROCEDURE Outer;
    PROCEDURE Inner(x: INTEGER): INTEGER;
    BEGIN RETURN x + 1 END Inner;
  BEGIN
    IF Inner = Inner THEN ASSERT(FALSE) END
  END Outer;

BEGIN
  Outer
END TStrictNestedCompare.