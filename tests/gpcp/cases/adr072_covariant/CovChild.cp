MODULE CovChild;
  IMPORT CovBase;
  TYPE Child* = POINTER TO RECORD (CovBase.Base) END;
  PROCEDURE (c: Child) New*(): CovBase.Model;
    VAR m: CovBase.Model;
  BEGIN NEW(m); RETURN m END New;
END CovChild.
