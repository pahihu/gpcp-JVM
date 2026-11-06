(* ADR-223: a weak import must not shadow an explicit declaration. *)
MODULE WLibA;
  TYPE T* = POINTER TO RECORD v*: INTEGER END;
END WLibA.
