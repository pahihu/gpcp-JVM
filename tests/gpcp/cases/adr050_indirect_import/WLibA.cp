(* ADR-050: indirect (weak) imports are read recursively. *)
MODULE WLibA;
  TYPE T* = POINTER TO RECORD v*: INTEGER END;
  PROCEDURE Make*(): T;
    VAR t: T;
  BEGIN NEW(t); t.v := 42; RETURN t END Make;
END WLibA.
