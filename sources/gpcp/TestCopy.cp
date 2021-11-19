

(*
 * Issue raised by DeaDDooMER on github
 *)

MODULE TestCopy;
  IMPORT CPmain, Console;

  TYPE
    Type* = ARRAY 16 OF CHAR;

    File* = POINTER TO RECORD
      type-: Type;
      init: BOOLEAN;
    END;

  VAR
    a, b: File;

BEGIN
  NEW(a); 
  NEW(b); 
  b.type := "the type string";
  b.init := TRUE;
  a^ := b^;
  Console.WriteString("Copied string: ");
  IF a.init THEN 
    Console.WriteString(a.type)
  ELSE
    Console.WriteString("... bad copy");
  END;
  Console.WriteLn;
END TestCopy.


