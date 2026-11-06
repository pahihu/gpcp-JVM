(* ADR-064: INC/DEC on LONGINT converts the increment operand. *)
MODULE TIncDec;
  IMPORT CPmain, Console;
  PROCEDURE Run;
    VAR l: LONGINT; i: INTEGER; ok: BOOLEAN;
  BEGIN
    l := 10000000000; i := 5;
    INC(l, i); DEC(l, 3);
    i := 7; INC(i, 2); DEC(i, 1);
    ok := (l = 10000000002) & (i = 8);
    IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
    Console.WriteLn()
  END Run;
BEGIN Run END TIncDec.
