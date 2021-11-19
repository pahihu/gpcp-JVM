(*
 *  Demonstration of TYPEOF and RTS.TypeName
 *  This works for both JVM and NET targets.
 *)
MODULE TypeNames;
  IMPORT RTS, Console, CPmain;

  TYPE RecF = RECORD a,b,c : SHORTREAL END;

  VAR type  : RTS.NativeType;
      matrx : ARRAY 4,5 OF CHAR;
      recF  : RecF;
      name  : RTS.CharOpen;
      syObj : RTS.NativeObject;
      cpStr : ARRAY 16 OF CHAR;
      cpInt : INTEGER;

  BEGIN
      Console.WriteString("Implementation type for ARRAY 4,5 OF CHAR"); Console.WriteLn;
      type := TYPEOF(matrx);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      syObj := "blah";         (* syObj is a Native String    *)
      Console.WriteString("Implementation type of string in Object variable"); Console.WriteLn;
      type := TYPEOF(syObj);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      syObj := type;
      Console.WriteString("Implementation type of NativeType in Object variable"); Console.WriteLn;
      type := TYPEOF(syObj);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      NEW(syObj);
      Console.WriteString("Implementation type of Object in Object variable"); Console.WriteLn;
      type := TYPEOF(syObj);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      Console.WriteString("Implementation type for INTEGER"); Console.WriteLn;
      type := TYPEOF(cpInt);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      cpStr := "blah";         (* cpStr is a CP ARRAY OF CHAR *)
      Console.WriteString("Implementation type for ARRAY 16 OF CHAR"); Console.WriteLn;
      type := TYPEOF(cpStr);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      Console.WriteString("Implementation type for RecF = RECORD ... END"); Console.WriteLn;
      type := TYPEOF(RecF);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 

      Console.WriteString("Implementation type for b field of RecF (SHORTREAL)"); Console.WriteLn;
      type := TYPEOF(recF.b);
      name := RTS.TypeName(type);
      Console.WriteString(name); Console.WriteLn;
      Console.WriteLn(); 
  END TypeNames.

