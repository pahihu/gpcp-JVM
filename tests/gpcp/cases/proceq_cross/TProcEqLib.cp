(* fixProcEqual: library half of the cross-module equality case.
   Values are produced in this module and consumed/compared in the client,
   so the comparison key must be procedure identity, not wrapper class. *)
MODULE TProcEqLib;
  TYPE
    Hook* = PROCEDURE (x: INTEGER): INTEGER;
  VAR
    Shared*: Hook;
    Stored: Hook;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE GetDouble*(): Hook;
  BEGIN RETURN Double END GetDouble;

  PROCEDURE Store*(v: Hook);
  BEGIN Stored := v END Store;

  PROCEDURE Get*(): Hook;
  BEGIN RETURN Stored END Get;

  PROCEDURE Same*(a: Hook; b: Hook): BOOLEAN;
  BEGIN RETURN a = b END Same;

BEGIN
  Shared := Double
END TProcEqLib.
