(* Stage 3: a named exported procedure type and an imported procedure
   literal.  Library half. *)
MODULE TImportLitLib;
  TYPE
    Hook* = PROCEDURE (x: INTEGER): INTEGER;
  VAR
    Shared*: Hook;

  PROCEDURE Double*(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE GetDouble*(): Hook;
  BEGIN RETURN Double END GetDouble;

BEGIN
  Shared := Double
END TImportLitLib.
