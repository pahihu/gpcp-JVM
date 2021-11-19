MODULE TestAdr;
  IMPORT CPmain, Console, SYSTEM;

  TYPE Rec = RECORD a,b,c : INTEGER END;
       Arr = ARRAY 32 OF INTEGER;
       RPt = POINTER TO Rec;
       APt = POINTER TO Arr;

  VAR  rec : Rec;
       arr : Arr;
       rPt : RPt;
       aPt : APt;
       int : INTEGER;
       val : INTEGER;
       ptr : INTEGER;

  PROCEDURE DoIt(VAR x : INTEGER);
  BEGIN
    Console.WriteString("ADR(x)      ");
    Console.WriteHex(SYSTEM.ADR(x),8); Console.WriteLn;
    Console.WriteString("ADR(int)    ");
    Console.WriteHex(SYSTEM.ADR(int),8); Console.WriteLn;
    Console.WriteLn;
    Console.WriteString("ADR(rec)    ");
    Console.WriteHex(SYSTEM.ADR(rec),8); Console.WriteLn;
    Console.WriteString("ADR(rec.a)  ");
    Console.WriteHex(SYSTEM.ADR(rec.a),8); Console.WriteLn;
    Console.WriteString("ADR(rec.b)  ");
    Console.WriteHex(SYSTEM.ADR(rec.b),8); Console.WriteLn;
    Console.WriteString("ADR(rec.c)  ");
    Console.WriteHex(SYSTEM.ADR(rec.c),8); Console.WriteLn;
    Console.WriteLn;
    Console.WriteString("ADR(arr)    ");
    Console.WriteHex(SYSTEM.ADR(arr),8); Console.WriteLn;
    Console.WriteString("ADR(arr[0]) ");
    Console.WriteHex(SYSTEM.ADR(arr[0]),8); Console.WriteLn;
    Console.WriteString("ADR(arr[1]) ");
    Console.WriteHex(SYSTEM.ADR(arr[1]),8); Console.WriteLn;
    Console.WriteString("ADR(arr[2]) ");
    Console.WriteHex(SYSTEM.ADR(arr[2]),8); Console.WriteLn;
    Console.WriteLn;
    Console.WriteString("ADR(rPt)    ");
    Console.WriteHex(SYSTEM.ADR(rPt),8); Console.WriteLn;
    Console.WriteString("ADR(rPt^)   ");
    Console.WriteHex(SYSTEM.ADR(rPt^),8); Console.WriteLn;
    Console.WriteString("ADR(rPt.a)  ");
    Console.WriteHex(SYSTEM.ADR(rPt.a),8); Console.WriteLn;
    Console.WriteString("ADR(rPt.b)  ");
    Console.WriteHex(SYSTEM.ADR(rPt.b),8); Console.WriteLn;
    Console.WriteString("ADR(rPt.c)  ");
    Console.WriteHex(SYSTEM.ADR(rPt.c),8); Console.WriteLn;
    Console.WriteLn;
    Console.WriteString("ADR(aPt)    ");
    Console.WriteHex(SYSTEM.ADR(aPt),8); Console.WriteLn;
    Console.WriteString("ADR(aPt^)   ");
    Console.WriteHex(SYSTEM.ADR(aPt^),8); Console.WriteLn;
    Console.WriteString("ADR(aPt[0]) ");
    Console.WriteHex(SYSTEM.ADR(aPt[0]),8); Console.WriteLn;
    Console.WriteString("ADR(aPt[1]) ");
    Console.WriteHex(SYSTEM.ADR(aPt[1]),8); Console.WriteLn;
    Console.WriteLn;
  END DoIt;

BEGIN
  NEW(aPt);
  NEW(rPt);
  DoIt(int);

  FOR int := 0 TO 28 BY 4 DO
    Console.WriteString("GET(ADR(arr)+");
    Console.WriteInt(int, 2);
    Console.WriteString(",int)");
    SYSTEM.GET(SYSTEM.ADR(arr) + int, val);
    Console.WriteHex(val, 8); Console.WriteLn;
  END;
  Console.WriteLn;

  FOR int := 0 TO 7 DO
    SYSTEM.PUT(SYSTEM.ADR(arr[int]), int*4);
  END;

  FOR int := 0 TO 28 BY 4 DO
    Console.WriteString("GET(ADR(arr)+");
    Console.WriteInt(int, 2);
    Console.WriteString(",int)");
    SYSTEM.GET(SYSTEM.ADR(arr) + int, val);
    Console.WriteHex(val, 8); Console.WriteLn;
  END;
END TestAdr.

