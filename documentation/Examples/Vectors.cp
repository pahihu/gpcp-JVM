(*
 *  Simple tests on vector manipulation
 *  Tests for VECTOR OF {CHAR, INTEGER, value record, pointers}
 *)
MODULE Vectors;
  IMPORT CPmain, Console;

  TYPE ValRec = RECORD a,b : INTEGER END;
       PtrRec = POINTER TO ValRec;

  TYPE ChrVec = VECTOR OF CHAR;
       IntVec = VECTOR OF INTEGER;
       RecVec = VECTOR OF ValRec;
       PtrVec = VECTOR OF POINTER TO ValRec;

  VAR  chrVec : ChrVec;
       intVec : IntVec;
       recVec : RecVec;
       ptrVec : PtrVec;

  PROCEDURE TestChrVec(vec : ChrVec);
    VAR cpy, vCp : ChrVec;
        idx : INTEGER;
  BEGIN
    APPEND(vec, "0");
    APPEND(vec, "1");
    APPEND(vec, "3");

    cpy := vec;

    NEW(vCp, LEN(vec));
    FOR idx := 0 TO LEN(vec)-1 DO APPEND(vCp, vec[idx]) END;

    Console.WriteString("Character Vector"); Console.WriteLn;
    Console.Write(vec[0]);
    Console.Write(vec[1]);
    Console.Write(vec[2]); Console.WriteString(" Original vector"); Console.WriteLn;
    Console.Write(cpy[0]);
    Console.Write(cpy[1]);
    Console.Write(cpy[2]); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    Console.Write(vCp[0]);
    Console.Write(vCp[1]);
    Console.Write(vCp[2]); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;

    Console.WriteString("Mutated element [1] of original vector"); Console.WriteLn;
    vec[1] := 'X';
    Console.Write(vec[0]);
    Console.Write(vec[1]);
    Console.Write(vec[2]); Console.WriteString(" Original vector "); Console.WriteLn;
    Console.Write(cpy[0]);
    Console.Write(cpy[1]);
    Console.Write(cpy[2]); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    Console.Write(vCp[0]);
    Console.Write(vCp[1]);
    Console.Write(vCp[2]); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;
    Console.WriteLn;
  END TestChrVec;

  PROCEDURE TestIntVec(vec : IntVec);
    VAR cpy,vCp : IntVec; 
        idx : INTEGER;
  BEGIN
    APPEND(vec, 0);
    APPEND(vec, 1);
    APPEND(vec, 3);

    cpy := vec;

    NEW(vCp, LEN(vec));
    FOR idx := 0 TO LEN(vec)-1 DO APPEND(vCp, vec[idx]) END;

    Console.WriteString("Integer Vector"); Console.WriteLn;
    Console.WriteInt(vec[0],0);
    Console.WriteInt(vec[1],0);
    Console.WriteInt(vec[2],0); Console.WriteString(" Original vector"); Console.WriteLn;
    Console.WriteInt(cpy[0],0);
    Console.WriteInt(cpy[1],0);
    Console.WriteInt(cpy[2],0); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    Console.WriteInt(vCp[0],0);
    Console.WriteInt(vCp[1],0);
    Console.WriteInt(vCp[2],0); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;

    Console.WriteString("Mutated element 1 of original vector"); Console.WriteLn;
    vec[1] := 42;

    Console.WriteInt(vec[0],0);
    Console.WriteInt(vec[1],0);
    Console.WriteInt(vec[2],0); Console.WriteString(" Original vector"); Console.WriteLn;
    Console.WriteInt(cpy[0],0);
    Console.WriteInt(cpy[1],0);
    Console.WriteInt(cpy[2],0); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    Console.WriteInt(vCp[0],0);
    Console.WriteInt(vCp[1],0);
    Console.WriteInt(vCp[2],0); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;
    Console.WriteLn;
  END TestIntVec;

  PROCEDURE TestRecVec(vec : RecVec);
    VAR cpy, vCp : RecVec;
        idx : INTEGER;
        tmp : ValRec;
   (* --------------------- *)
    PROCEDURE WriteRec(IN r : ValRec);
    BEGIN
      Console.Write('{'); Console.WriteInt(r.a,1);
      Console.Write(','); Console.WriteInt(r.b,1);
      Console.Write('}'); Console.Write(" ");
    END WriteRec;
   (* --------------------- *)
    PROCEDURE MkRec(a,b : INTEGER; OUT r : ValRec);
    BEGIN
      r.a := a; r.b := b;
    END MkRec;
   (* --------------------- *)
  BEGIN
    MkRec(0,1, tmp); APPEND(vec, tmp);
    MkRec(2,3, tmp); APPEND(vec, tmp);
    MkRec(4,5, tmp); APPEND(vec, tmp);

    cpy := vec;

    NEW(vCp, LEN(vec));
    FOR idx := 0 TO LEN(vec)-1 DO APPEND(vCp, vec[idx]) END;

    Console.WriteString("Value Record Vector"); Console.WriteLn;
    WriteRec(vec[0]);
    WriteRec(vec[1]);
    WriteRec(vec[2]); Console.WriteString(" Original vector"); Console.WriteLn;
    WriteRec(cpy[0]);
    WriteRec(cpy[1]);
    WriteRec(cpy[2]); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    WriteRec(vCp[0]);
    WriteRec(vCp[1]);
    WriteRec(vCp[2]); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;

    Console.WriteString("Mutate elements of copies"); Console.WriteLn;
    cpy[1].a := 77;
    vCp[2].b := 99;

    WriteRec(vec[0]);
    WriteRec(vec[1]);
    WriteRec(vec[2]); Console.WriteString(" Original vector"); Console.WriteLn;
    WriteRec(cpy[0]);
    WriteRec(cpy[1]);
    WriteRec(cpy[2]); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    WriteRec(vCp[0]);
    WriteRec(vCp[1]);
    WriteRec(vCp[2]); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;
    Console.WriteLn;
  END TestRecVec;

  PROCEDURE TestPtrVec(vec : PtrVec);
    VAR cpy,vCp : PtrVec;
        idx : INTEGER;
   (* --------------------- *)
    PROCEDURE WriteRec(r : PtrRec);
    BEGIN
      Console.Write('{'); Console.WriteInt(r.a,1);
      Console.Write(','); Console.WriteInt(r.b,1);
      Console.Write('}'); Console.Write(" ");
    END WriteRec;
   (* --------------------- *)
    PROCEDURE MkPtr(a,b : INTEGER) : PtrRec;
      VAR p : PtrRec;
    BEGIN
      NEW(p); p.a := a; p.b := b; RETURN p;
    END MkPtr;
   (* --------------------- *)
  BEGIN
    APPEND(vec, MkPtr(0,1));
    APPEND(vec, MkPtr(2,3));
    APPEND(vec, MkPtr(4,5));

    cpy := vec;

    NEW(vCp, LEN(vec));
    FOR idx := 0 TO LEN(vec)-1 DO APPEND(vCp, vec[idx]) END;

    Console.WriteString("Reference Record Vector"); Console.WriteLn;
    WriteRec(vec[0]);
    WriteRec(vec[1]);
    WriteRec(vec[2]); Console.WriteString(" Original vector"); Console.WriteLn;
    WriteRec(cpy[0]);
    WriteRec(cpy[1]);
    WriteRec(cpy[2]); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    WriteRec(vCp[0]);
    WriteRec(vCp[1]);
    WriteRec(vCp[2]); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;

    Console.WriteString("Mutate elements of copies"); Console.WriteLn;
    cpy[1].a := 77;
    vCp[2].b := 99;

    WriteRec(vec[0]);
    WriteRec(vec[1]);
    WriteRec(vec[2]); Console.WriteString(" Original vector"); Console.WriteLn;
    WriteRec(cpy[0]);
    WriteRec(cpy[1]);
    WriteRec(cpy[2]); Console.WriteString(" Entire assign copy"); Console.WriteLn;
    WriteRec(vCp[0]);
    WriteRec(vCp[1]);
    WriteRec(vCp[2]); Console.WriteString(" Elem-by-elem copy"); Console.WriteLn;

    Console.WriteLn;
  END TestPtrVec;

BEGIN
  NEW(intVec, 8);
  TestIntVec(intVec);

  NEW(chrVec, 8);
  TestChrVec(chrVec);

  NEW(recVec, 8);
  TestRecVec(recVec);

  NEW(ptrVec, 8);
  TestPtrVec(ptrVec);

END Vectors.



