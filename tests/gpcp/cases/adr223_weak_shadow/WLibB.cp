MODULE WLibB;
  IMPORT WLibA;
  TYPE T* = WLibA.T;
  PROCEDURE Get*(): T;
    VAR t: T;
  BEGIN NEW(t); t.v := 1; RETURN t END Get;
END WLibB.
