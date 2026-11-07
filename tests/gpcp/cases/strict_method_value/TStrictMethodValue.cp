(* Strict CP (report Ch. 6.5): a method is not a procedure value. *)
MODULE TStrictMethodValue;
  TYPE
    T = RECORD n: INTEGER END;
    Hook = PROCEDURE (x: INTEGER): INTEGER;

  VAR
    t: T;
    f: Hook;

  PROCEDURE (VAR self: T) Add(x: INTEGER): INTEGER, NEW;
  BEGIN RETURN self.n + x END Add;

BEGIN
  t.n := 1;
  f := t.Add
END TStrictMethodValue.