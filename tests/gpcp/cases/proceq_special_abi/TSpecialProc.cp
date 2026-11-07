(* fixProcEqual ABI: procedure values cross the boundary into a native
   (-special) module.  The generated Proc$Lit$ wrappers must extend the
   named Java host class expected by the hand-written body. *)
MODULE TSpecialProc;
  IMPORT CPmain, Console, SpecialProc;

  VAR
    h: SpecialProc.Handler;
    c: SpecialProc.Command;

  PROCEDURE H(x: INTEGER);
  BEGIN Console.WriteInt(x, 0) END H;

  PROCEDURE C(x: INTEGER);
  BEGIN Console.WriteInt(x, 0) END C;

BEGIN
  h := H;
  c := C;
  SpecialProc.Install(h);
  SpecialProc.Run(c);
  IF h = h THEN Console.WriteString(" eq") END;
  IF h # c THEN Console.WriteString(" ne") END;
 (* Handler and Command are distinct -special host classes with the same
    signature; both wrappers implement ProcKey, so the same procedure
    compares equal across them. *)
  c := H;
  IF h = c THEN Console.WriteString(" cross") END;
  Console.WriteLn()
END TSpecialProc.