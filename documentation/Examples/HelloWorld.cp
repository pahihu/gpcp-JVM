MODULE HelloWorld;
  IMPORT CPmain,	(* so this will be a .exe rather than a .dll	*)
	 Console,	(* to get console input-output operations	*)
	 ProgArgs;	(* to get access to any command line arguments	*)

  CONST greet = "Hello gpcp world";
  VAR	argNn : ARRAY 64 OF CHAR;
	index : INTEGER;
BEGIN
  Console.WriteString(greet);
  Console.WriteLn;
  IF ProgArgs.ArgNumber() > 0 THEN
    Console.WriteString("Actually, HelloWorld needs no arguments");
    Console.WriteLn;
    FOR index := 0 TO ProgArgs.ArgNumber() - 1 DO
      ProgArgs.GetArg(index, argNn);
      Console.WriteInt(index, 2);
      Console.Write(' ');
      Console.WriteString(argNn);
      Console.WriteLn;
    END;
  END;
END HelloWorld.
