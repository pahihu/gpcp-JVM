(* Strict CP: a bound method is not a procedure value, including when it is
   assigned to a procedure-typed record field. *)
MODULE TStrictMethodField;
  TYPE
    T = RECORD n: INTEGER END;
    Hook = PROCEDURE (x: INTEGER): INTEGER;
    Holder = RECORD cb: Hook END;

  VAR
    t: T;
    h: Holder;

  PROCEDURE (VAR self: T) Add(x: INTEGER): INTEGER, NEW;
  BEGIN RETURN self.n + x END Add;

BEGIN
  t.n := 1;
  h.cb := t.Add
END TStrictMethodField.