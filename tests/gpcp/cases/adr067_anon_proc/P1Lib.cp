(* ADR-067: anonymous procedure types get a structural name, so a procedure
   value can be passed between modules (same signature => same wrapper class). *)
MODULE P1Lib;
  VAR hook*: PROCEDURE (x: INTEGER): INTEGER;
  PROCEDURE Inc*(x: INTEGER): INTEGER;
  BEGIN RETURN x + 1 END Inc;
BEGIN hook := Inc END P1Lib.
