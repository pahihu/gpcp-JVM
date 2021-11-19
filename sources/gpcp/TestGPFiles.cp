

MODULE TestGPFiles;
  IMPORT CPmain, Console, ProgArgs, GPFiles, RTS;

  CONST greet = "Hello ASM World";
  VAR   indx : INTEGER;
        argN : INTEGER;
        argX : ARRAY 256 OF CHAR;

  PROCEDURE Process(IN a : ARRAY OF CHAR);
    VAR idx : INTEGER;
        fls : POINTER TO ARRAY OF RTS.CharOpen;
        nam : RTS.CharOpen;
  BEGIN
    Console.WriteString("arg " + a);
    Console.WriteLn;
    fls := GPFiles.FileList(a);
    FOR idx := 0 TO LEN(fls) - 1 DO
      Console.WriteString("    " + fls[idx]^);
      Console.WriteLn;
    END;
  RESCUE (x)
    Console.WriteString("GPFiles.FileList threw ");
    Console.WriteString(RTS.getStr(x));
    Console.WriteLn;
  END Process;

BEGIN
  argN := ProgArgs.ArgNumber();
  Console.WriteString("TestGPFiles");
  Console.WriteInt(argN, 0);
  Console.WriteString(" arguments");
  Console.WriteLn;
  FOR indx := 0 TO argN - 1 DO
    ProgArgs.GetArg(indx, argX);
    Process(argX);
  END;
END TestGPFiles.

