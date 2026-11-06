(* ADR-020/021: empty set literal and set complement (-{} = all bits). *)
MODULE TSet;
  IMPORT CPmain, Console;
  VAR s, all: SET; ok: BOOLEAN;
BEGIN
  s := {};
  all := -{};
  ok := (s = {}) & (all = {0..31});
  IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TSet.
