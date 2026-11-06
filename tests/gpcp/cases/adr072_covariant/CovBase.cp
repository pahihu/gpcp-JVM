(* ADR-072: covariant result narrowing needs a bridge method. *)
MODULE CovBase;
  TYPE Base* = POINTER TO ABSTRACT RECORD END;
       Model* = POINTER TO RECORD (Base) END;
  PROCEDURE (b: Base) New*(): Base, NEW, ABSTRACT;
  PROCEDURE (m: Model) New*(): Base;
  BEGIN RETURN m END New;
END CovBase.
