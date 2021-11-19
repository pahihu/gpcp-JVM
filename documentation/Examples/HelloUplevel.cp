(*
** Tests uplevel access to local variables
** from nested procedures. Should generate
** warning messaged during compilation.
*)

MODULE HelloUplevel;
  IMPORT CPmain, RTS, Console;

  VAR arg : INTEGER;

  PROCEDURE Foo*(i : INTEGER) : INTEGER;
    VAR copy : INTEGER;

    PROCEDURE Bar() : INTEGER;
    BEGIN
      RETURN copy;
    END Bar;

  BEGIN
    copy := i;
    RETURN Bar();
  END Foo;

BEGIN
  FOR arg := 0 TO 42 DO
    IF arg # Foo(arg) THEN RTS.Throw("Uplevel addressing failed") END;
  END;
  Console.WriteString("HelloUplevel test passed"); Console.WriteLn;
END HelloUplevel.
