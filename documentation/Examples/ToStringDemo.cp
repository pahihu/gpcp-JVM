(*
 * Imports mscorlib ==> only works on .NET
 *)

MODULE ToStringDemo;

  IMPORT Sys := mscorlib_System, RTS, CPmain;

  TYPE Coord  = POINTER TO RECORD (Sys.Object)
                  x, y : REAL; s : RTS.CharOpen;  
                END;

  VAR arr : POINTER TO ARRAY OF Sys.Object;

  (*
   *  This proc allocates an initialized object of the MyBlah type.
   *)
  PROCEDURE newCoord(name : RTS.CharOpen; x,y : REAL) : Coord;
    VAR rslt : Coord;
  BEGIN
    NEW(rslt);
    rslt.x := x;
    rslt.y := y;
    rslt.s := name;
    RETURN rslt;
  END newCoord;
    
  (*
   *  This method overrides Sys.Object.ToString(). The method 
   *  inherited from object would simply return the string "Coord".
   *)
  PROCEDURE (pt : Coord)ToString() : Sys.String;
    CONST format = "{0}{{{1},{2}}}";
    VAR   tag : Sys.String;
  BEGIN
    (*
     *  We must transform the CharOpen to a System string.
     *  We must also generate objects for the REALs. Component Pascal
     *  does not automatically box value types, and even with the gpcp BOX 
     *  extension will not box a value of a primitive type such as REAL.
     *)
    IF pt.s # NIL THEN tag := MKSTR(pt.s^) ELSE tag := "anon" END;
    RETURN Sys.String.Format(format, 
        tag, Sys.Convert.ToString(pt.x), Sys.Convert.ToString(pt.y));
  END ToString;

BEGIN
  NEW(arr, 3);
  arr[0] := newCoord(BOX("Start"), 0.0, 0.0);
  arr[1] := newCoord(NIL, 0.5, 0.5);
  arr[2] := newCoord(BOX("End"), 1.0, 1.0);
  Sys.Console.WriteLine("Path: {0}, {1}, {2}", arr);
END ToStringDemo.

