


MODULE JvmParams;

  IMPORT 
         Sys := java_lang, 
         ProgArgs, 
         RTS, 
         CPmain;

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
  PROCEDURE (this : MyBlah)toString() : Sys.String;
    VAR objArr : ARRAY 1 OF Sys.Object;
  BEGIN
    (*
     *  We must transform the CharOpen to a System string.
     *  We must also generate an object from the integer. Component Pascal
     *  does not automatically box value types, and even with the gpcp BOX 
     *  extension will not box a value of a primitive type such as INTEGER.
     *)
    objArr[0] := Sys.String.valueOf(this.a);
    RETURN Sys.String.format(MKSTR(this.s^), objArr);
  END toString;

BEGIN
  j := ProgArgs.ArgNumber();
  NEW(arr, 8);
  FOR i := 0 TO 7 DO
    IF i < j THEN 
      ProgArgs.GetArg(i, arg);
      arr[i] := MKSTR(arg);
    ELSE
      arr[i] := NewBlah(i, BOX("arg %s missing"));
    END;
  END;
  Sys.System.out.println(Sys.String.format("Args: %s, %s, %s, %s, %s, %s, %s, %s", arr^));
END JvmParams.

