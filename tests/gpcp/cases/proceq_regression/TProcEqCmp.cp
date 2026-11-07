(* fixProcEqual regression: only procedure-typed comparisons may change.
   Pointer, string, CHAR, integer, REAL and SET comparisons keep their
   existing semantics. *)
MODULE TProcEqCmp;
  IMPORT CPmain, Console;

  TYPE
    P = POINTER TO RECORD x: INTEGER END;

  VAR
    ok: BOOLEAN;
    p, q: P;
    s, t: ARRAY 8 OF CHAR;
    i, j: INTEGER;
    r: REAL;
    set: SET;

BEGIN
  NEW(p); q := p; NEW(p);
  s := 'abc'; t := 'abc';
  i := 7; j := 7; r := 1.5; set := {1,2};

  ok := (p # q) & (q = q) & (p # NIL) &
        (s = t) & (s # 'abd') &
        ("A" = "A") & ("A" # "B") &
        (i = j) & (i # 8) &
        (r = 1.5) &
        (set = {1,2});

  IF ok THEN Console.WriteString("PASS") ELSE Console.WriteString("FAIL") END;
  Console.WriteLn()
END TProcEqCmp.
