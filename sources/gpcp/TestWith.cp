

MODULE TestWith;
  IMPORT CPmain, Console, RTS;

  TYPE Base = POINTER TO EXTENSIBLE RECORD END;
       Extn = POINTER TO EXTENSIBLE RECORD (Base) END;
       Fnal = POINTER TO RECORD (Extn) END;

  VAR  b : Base;
       e : Extn;
       f : Fnal;

  PROCEDURE DoWith3( p : Base );
  BEGIN
    WITH 
      p : Fnal DO Console.WriteString( "Type is Fnal" );
    | p : Extn DO Console.WriteString( "Type is Extn" );
    | p : Base DO Console.WriteString( "Type is Base" );
    END;
    Console.WriteLn;
  END DoWith3;

  PROCEDURE DoWith2( p : Base );
  BEGIN
    WITH 
      p : Fnal DO Console.WriteString( "Type is Fnal" );
    | p : Extn DO Console.WriteString( "Type is Extn" );
    END;
    Console.WriteLn;
  RESCUE ( x )
    Console.WriteString( RTS.getStr( x )^ );
    Console.WriteLn;
  END DoWith2;

BEGIN
  NEW( b );
  NEW( e );
  NEW( f );

  Console.WriteString( "Test three type-cases, no trap" ); Console.WriteLn;
  DoWith3( f );
  DoWith3( e );
  DoWith3( b );

  Console.WriteString( "Test three type-cases, last should trap" ); Console.WriteLn;
  DoWith2( f );
  DoWith2( e );
  DoWith2( b );

END TestWith.

