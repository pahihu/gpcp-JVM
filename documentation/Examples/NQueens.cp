MODULE NQueens;
  IMPORT RTS, Console, CPmain;

  CONST max    = 15;

  TYPE	Board  = ARRAY max+1 OF SET;

  VAR   board  : Board;
	freeR  : SET;
	upDiag : SET;
	dnDiag : SET;
 	boardSize  : INTEGER;
	nSolutions : INTEGER;
	timeTicks : LONGINT;
	dateTime  : ARRAY 64 OF CHAR;

  PROCEDURE Dump(size : INTEGER);
    VAR i : INTEGER;
    PROCEDURE Row(s : SET; l : INTEGER);
      VAR j : INTEGER;
    BEGIN
      FOR j := 0 TO l-1 DO
	IF j IN s THEN Console.Write("X") ELSE Console.Write(".") END;
      END;
      Console.WriteLn;
    END Row;
  BEGIN
    Console.WriteString("---------------------------------"); Console.WriteLn;
    FOR i := 0 TO size-1 DO Row(board[i], size) END;
    Console.WriteString("---------------------------------"); Console.WriteLn;
    Row(freeR, 31);
    Row(upDiag, 31);
    Row(dnDiag, 31);
  END Dump;

  PROCEDURE Clear();
    VAR i : INTEGER;
  BEGIN
    FOR i := 0 TO max DO board[i] := {} END;
    freeR := {0 .. max};
    upDiag := {0 .. 31};
    dnDiag := {0 .. 31};
  END Clear;

  PROCEDURE free(i,j : INTEGER) : BOOLEAN;
  BEGIN
    RETURN  (j IN freeR )
	& ((i+j) IN upDiag)
	& ((max+i-j) IN dnDiag);
  END free;

  PROCEDURE Insert(i,j : INTEGER);
  BEGIN
    INCL(board[i],j); (* insert into board *)
    EXCL(freeR,j);
    EXCL(upDiag, i+j);
    EXCL(dnDiag, max+i-j);
  END Insert;
 
  PROCEDURE Remove(i,j : INTEGER);
  BEGIN
    EXCL(board[i],j);
    INCL(freeR,j);
    INCL(upDiag, i+j);
    INCL(dnDiag, max+i-j);
  END Remove;

  PROCEDURE Try(rank : INTEGER; size : INTEGER);
    VAR file : INTEGER;
  BEGIN
    FOR file := 0 TO size-1 DO
      IF free(rank,file) THEN
	IF rank = size-1 THEN 
	  INC(nSolutions);
(*
	  Insert(rank,file); Dump(size); Remove(rank,file);
 *)
	ELSE
	  Insert(rank,file); Try(rank+1, size); Remove(rank,file);
	END;
      END;
    END;
  END Try;

BEGIN
  RTS.GetDateString(dateTime);
  Console.WriteString(dateTime); Console.WriteLn;
  timeTicks := RTS.GetMillis();
  FOR boardSize := 8 TO 14 DO
    Clear();
    nSolutions := 0;
    Try(0, boardSize);
    Console.WriteString("Number of solutions for ");
    Console.WriteInt(boardSize, 0);
    Console.WriteString(" is ");
    Console.WriteInt(nSolutions,0);
    Console.WriteLn;
  END;
  timeTicks := RTS.GetMillis() - timeTicks;
  Console.WriteString("NQueens ending ... elapsed time ="); 
  Console.WriteInt(SHORT(timeTicks), 0); 
  Console.WriteString(" milliseconds"); 
  Console.WriteLn;
  RTS.GetDateString(dateTime);
  Console.WriteString(dateTime); Console.WriteLn;
END NQueens.
