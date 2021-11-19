(*
 * Testing MKSTR and BOX functionality
 * Also creation of "BangString" literals
 * with embedded control and NUL chars.
 * 
 * Should work with identical output on
 * JVM and CLR versions.
 *)

MODULE MkstrAndBox;
  IMPORT CPmain, Console, RTS;

  CONST lit* = !"abc\0def";

  VAR arr : ARRAY 12 OF CHAR;
      str : RTS.NativeString; 
      ptr : RTS.CharOpen;
      idx : INTEGER;
      chr : CHAR;

BEGIN
  arr := lit;
  Console.WriteString("Chars of arr, after arr := lit"); Console.WriteLn;
  Console.WriteString("LEN arr "); Console.WriteInt(LEN(arr),0); Console.WriteLn;
  Console.WriteString("LEN lit "); Console.WriteInt(LEN(lit),0); Console.WriteLn;
  FOR idx := 0 TO LEN(arr) - 1 DO
    Console.Write(' ');
    Console.Write(arr[idx]);
    Console.WriteInt(ORD(arr[idx]), 4);
  END;
  Console.WriteLn;
  Console.WriteLn;

  str := MKSTR(lit);
  Console.WriteString("Chars of str, after str := MKSTR(lit)"); Console.WriteLn;
  Console.WriteString("LEN str "); Console.WriteInt(RTS.Length(str),0); Console.WriteLn;
  FOR idx := 0 TO RTS.Length(str) - 1 DO
    chr := RTS.CharAtIndex(str,idx);
    Console.Write(' ');
    Console.Write(chr);
    Console.WriteInt(ORD(chr),4);
  END;
  Console.WriteLn;
  Console.WriteLn;

  Console.WriteString("Chars of str, after str := MKSTR(arr$)"); Console.WriteLn;
  str := MKSTR(arr$);
  Console.WriteString("LEN str "); Console.WriteInt(RTS.Length(str),0); Console.WriteLn;
  FOR idx := 0 TO RTS.Length(str) - 1 DO
    chr := RTS.CharAtIndex(str,idx);
    Console.Write(' ');
    Console.Write(chr);
    Console.WriteInt(ORD(chr),4);
  END;
  Console.WriteLn;
  Console.WriteLn;

  ptr := BOX(lit);
  Console.WriteString("Chars of ptr, after ptr := BOX(lit)"); Console.WriteLn;
  Console.WriteString("LEN lit "); Console.WriteInt(LEN(lit),0); Console.WriteLn;
  Console.WriteString("LEN ptr "); Console.WriteInt(LEN(ptr),0); Console.WriteLn;
  FOR idx := 0 TO LEN(ptr) - 1 DO
    Console.Write(' ');
    Console.Write(ptr[idx]);
    Console.WriteInt(ORD(ptr[idx]), 4);
  END;
  Console.WriteLn;
  Console.WriteLn;

  arr := lit;
  ptr := BOX(arr);
  Console.WriteString("Chars of ptr, after ptr := BOX(arr)"); Console.WriteLn;
  Console.WriteString("LEN arr "); Console.WriteInt(LEN(arr),0); Console.WriteLn;
  Console.WriteString("LEN ptr "); Console.WriteInt(LEN(ptr),0); Console.WriteLn;
  FOR idx := 0 TO LEN(ptr) - 1 DO
    Console.Write(' ');
    Console.Write(ptr[idx]);
    Console.WriteInt(ORD(ptr[idx]), 4);
  END;
  Console.WriteLn;
  Console.WriteLn;
  
  ptr := BOX(arr$);
  Console.WriteString("Chars of ptr, after ptr := BOX(arr$)"); Console.WriteLn;
  Console.WriteString("LEN arr$ "); Console.WriteInt(LEN(arr$),0); Console.WriteLn;
  Console.WriteString("LEN ptr "); Console.WriteInt(LEN(ptr),0); Console.WriteLn;
  FOR idx := 0 TO LEN(ptr) - 1 DO
    Console.Write(' ');
    Console.Write(ptr[idx]);
    Console.WriteInt(ORD(ptr[idx]), 4);
  END;
  Console.WriteLn;
END MkstrAndBox.

