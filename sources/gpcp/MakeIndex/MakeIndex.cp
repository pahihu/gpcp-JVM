(*
New BSD License (BSD)
Copyright (c) 2000 - 2010, K John Gough

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

* Neither the name of Queensland University of Technology nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*)


MODULE MakeIndex;

  IMPORT 
        RTS,
        Console,
        Error,
        CPmain,
        ProgArgs,
        Btd := BiTypeDefs,
        Bsh := BiStateHandler;

(* ============================================================ *)

  VAR badOption : BOOLEAN;

  VAR idx : INTEGER;
      arg : ARRAY 256 OF CHAR;

  VAR appState : Bsh.State;

(* ============================================================ *)

  PROCEDURE ParseOption(opt : ARRAY OF CHAR) : BOOLEAN;
    VAR rst : Btd.CharOpen;
        arg : ARRAY 256 OF CHAR;
   (* ----------------------------------------- *)
   (*  Note: str is mutable, pat is immutable   *)
   (* ----------------------------------------- *)
    PROCEDURE StartsWith(str : ARRAY OF CHAR; IN pat : ARRAY OF CHAR) : BOOLEAN;
    BEGIN (* friendly warping of options *)
      str[LEN(pat$)] := 0X;
      RETURN str = pat;
    END StartsWith;
   (* ----------------------------------------- *)
    PROCEDURE SuffixString(IN str : ARRAY OF CHAR; ofst : INTEGER) : Btd.CharOpen;
      VAR len : INTEGER;
          idx : INTEGER;
          out : Btd.CharOpen;
    BEGIN
      len := LEN(str$) - ofst;
      IF len > 0 THEN
        NEW(out, len + 1);
        FOR idx := 0 TO len - 1 DO
          out[idx] := str[ofst + idx];
        END;
        out[len] := 0X;
        RETURN out;
      END;
      RETURN NIL;
    END SuffixString;
   (* ----------------------------------------- *)
  BEGIN
    IF opt[0] = '/' THEN opt[0] := '-' END;
    IF opt[4] = '=' THEN opt[4] := ':' END;
    IF StartsWith(opt, "-dst:") THEN
      appState.dstPath := SuffixString(opt, 5);
    ELSIF (LEN(opt$) > 4) & StartsWith("-verbose", opt) THEN
      appState.verbose := TRUE;  
    ELSE
      RETURN FALSE;
    END;
    RETURN TRUE;
  END ParseOption;

(* ============================================================ *)

BEGIN (* Static code of Module *)
  NEW(appState);
  IF ProgArgs.ArgNumber() = 0 THEN
    Console.WriteString("Usage: MakeIndex [-verb] -dst:dir"); Console.WriteLn;
    Console.WriteString("     -dst:dir    - find symfiles in directory 'dir'"); Console.WriteLn;
    Console.WriteString("     -verb[ose]  - emit progress information."); Console.WriteLn;
    Console.WriteString("Output file is 'dir\index.html'"); Console.WriteLn;
    HALT(0);
  END;
  FOR idx := 0 TO ProgArgs.ArgNumber() - 1 DO
    ProgArgs.GetArg(idx, arg);
    badOption := ~ParseOption(arg);
    IF badOption THEN
      Error.WriteString("Bad option: " + arg$ + " HALTING.");
      Error.WriteLn;
      HALT(1);
    END;
  END;
  IF appState.dstPath = NIL THEN
    Error.WriteString("-dst:dir argument is mandatory, HALTING");
    Error.WriteLn;
    HALT(1);
  END;
  appState.InitPackageList();
  appState.ListFiles();
  appState.WriteIndex();
END MakeIndex.

(* ============================================================ *)
