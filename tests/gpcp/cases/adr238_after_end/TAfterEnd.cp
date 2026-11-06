(* ADR-238: the scanner must not scan non-ASCII text after END <Module>. *)
MODULE TAfterEnd;
  IMPORT CPmain, Console;
BEGIN
  Console.WriteString("PASS");
  Console.WriteLn()
END TAfterEnd.
Привет, это текст после конца модуля.
