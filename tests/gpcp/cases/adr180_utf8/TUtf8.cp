(* ADR-180/188: UTF-8 source is decoded into CHAR, not treated as bytes. *)
MODULE TUtf8;
  IMPORT CPmain, Console;
BEGIN
  Console.WriteString("Привет, мир");
  Console.WriteLn()
END TUtf8.
