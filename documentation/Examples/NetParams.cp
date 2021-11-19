

MODULE NetParams;

  IMPORT Sys := mscorlib_System, RTS, ProgArgs, CPmain;

  TYPE MyBlah = POINTER TO RECORD (Sys.Object) 
                  a : INTEGER;
                  s : RTS.CharOpen;  (* shorthand for POINTER TO ARRAY OF CHAR *)
                END;

  VAR arr : POINTER TO ARRAY OF Sys.Object;
      arg : ARRAY 256 OF CHAR;
      i, j : INTEGER;
  (*
   *  This proc allocates an initialized object of the MyBlah type.
   *)
  PROCEDURE NewBlah(idx : INTEGER; msg : RTS.CharOpen) : MyBlah;
    VAR result : MyBlah;
  BEGIN
    NEW(result);
    result.a := idx;
    result.s := msg;
    RETURN result;
  END NewBlah;
    
  (*
   *  This method overrides Sys.Object.ToString(). The method 
   *  inherited from object would simply return the string "MyBlah".
   *)
  PROCEDURE (this : MyBlah)ToString() : Sys.String;
    VAR o : Sys.Object;
  BEGIN
    (*
     *  We must transform the CharOpen to a System string.
     *  We must also generate an object from the integer. Component Pascal
     *  does not automatically box value types, and even with the gpcp BOX 
     *  extension will not box a value of a primitive type such as INTEGER.
     *)
    RETURN Sys.String.Format(MKSTR(this.s^), Sys.Convert.ToString(this.a));
  END ToString;

BEGIN
  j := ProgArgs.ArgNumber();
  NEW(arr, 8);
  FOR i := 0 TO 7 DO
    IF i < j THEN 
      ProgArgs.GetArg(i, arg);
      arr[i] := MKSTR(arg);
    ELSE
      arr[i] := NewBlah(i, BOX("arg {0} missing"));
    END;
  END;
  Sys.Console.WriteLine("Args: {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}", arr);
END NetParams.
