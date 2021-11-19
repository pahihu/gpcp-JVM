(*
 * Test import of string with embedded NUL character
 *)

MODULE TestBangString;
  IMPORT 
    Tst := ExportBangString, 
    Console,
    CPmain;

  VAR copy : ARRAY 16 OF CHAR;
      float : SHORTREAL;
      dbl   : REAL;
      idx   : INTEGER;
      len   : INTEGER;
BEGIN
  Console.WriteString("Testing import of litString with embedded NUL char"); 
  Console.WriteLn;

  FOR idx := 0 TO LEN(copy) - 1 DO copy[idx] := 0FFX END;
  Console.WriteString("Initial fixed length array ... in HEX"); Console.WriteLn;
  FOR idx := 0 TO LEN(copy) - 1 DO
    Console.WriteHex(ORD(copy[idx]), 3); 
  END;
  Console.WriteLn;

  Console.WriteString("Source of bang string was = " + Tst.verbatimFoo); 
  Console.WriteLn;
  len := LEN(Tst.bangStrFoo);
  Console.WriteString("Length of BangString = "); 
  Console.WriteInt(len, 0); Console.WriteLn;
  
  copy := Tst.bangStrFoo;

  Console.WriteString("Characters in string ... in HEX"); Console.WriteLn;
  FOR idx := 0 TO len - 1 DO
    Console.WriteHex(ORD(copy[idx]), 3); 
  END;
  Console.WriteLn;

  Console.WriteString("Array after string copied in ... in HEX"); Console.WriteLn;
  FOR idx := 0 TO LEN(copy) - 1 DO
    Console.WriteHex(ORD(copy[idx]), 3); 
  END;
  Console.WriteLn;
END TestBangString.
