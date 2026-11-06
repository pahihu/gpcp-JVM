(* Native interface module used by the ADR-013 / ADR-044 tests. *)
SYSTEM MODULE NativeLib;
  TYPE Copyable* = RECORD x*: INTEGER END;
       Extensible* = EXTENSIBLE RECORD y*: INTEGER END;
END NativeLib.
