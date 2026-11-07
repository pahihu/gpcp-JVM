(* fixProcEqual ABI: named procedure types declared in a -special
   interface must keep their stable Java class name.  Handler and
   Command have identical Component Pascal signatures, so a structural
   naming scheme would collapse them into one class and break the
   hand-written Java body below. *)
SYSTEM MODULE SpecialProc;
  TYPE
    Handler* = PROCEDURE (x: INTEGER);
    Command* = PROCEDURE (x: INTEGER);

  PROCEDURE Install*(h: Handler);
  PROCEDURE Run*(c: Command);
END SpecialProc.