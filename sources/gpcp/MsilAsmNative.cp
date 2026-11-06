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

(* ============================================================ *)
(**	Interface to the ILASM Byte-code assembler.		*)
(*      Copyright (c) John Gough 1999 -- 2002.			*)
(*	K John Gough, 10th June 1999				*)
(*	Modifications:						*)
(*		Version for GPCP V0.3 April 2000 (kjg)		*)
(* ============================================================ *)

MODULE MsilAsm;
  IMPORT 
      RTS,
      Console,
      CompState,
      GPCPcopyright,
      Diag := "[System]System.Diagnostics";

  VAR asm  : Diag.Process;

  PROCEDURE Init*();
  BEGIN
    IF asm = NIL THEN
      NEW(asm);
      asm.get_StartInfo().set_FileName("ilasm");
      asm.get_StartInfo().set_CreateNoWindow(TRUE);
      asm.get_StartInfo().set_UseShellExecute(FALSE);
    END;
  END Init;

  PROCEDURE Assemble*(IN file : ARRAY OF CHAR; 
		      IN optn : ARRAY OF CHAR;	(* "/debug" or "" *)
			 main : BOOLEAN); 	(* /exe or /dll   *)
    VAR retCode : INTEGER;
        optNm   : RTS.NativeString;
        suffx   : RTS.NativeString;
        fName   : RTS.NativeString;
        ignore  : BOOLEAN;
  BEGIN
    fName := MKSTR(file);
    IF main THEN
      optNm := "/exe "; suffx := ".exe";
    ELSE
      optNm := "/dll "; suffx := ".dll";
    END;
    optNm := optNm + MKSTR(optn) + " ";
    asm.get_StartInfo().set_Arguments(optNm+"/nologo /quiet "+fName+".il");
    ignore := asm.Start();
    asm.WaitForExit();
    retCode := asm.get_ExitCode();
    IF retCode # 0 THEN
      Console.WriteString("#gpcp: ilasm FAILED");
      Console.WriteInt(retCode, 0);
    ELSIF ~CompState.quiet THEN
      Console.WriteString("#gpcp: Created " + fName + suffx);
    END;
    Console.WriteLn;
  END Assemble;

  PROCEDURE DoAsm*(IN file : ARRAY OF CHAR; 
		   IN optn : ARRAY OF CHAR;	(* "/debug" or "" *)
		      main : BOOLEAN; 		(* /exe or /dll   *)
		      vbse : BOOLEAN; 		(* verbose or not *)
		  OUT rslt : INTEGER);		(* ilasm ret-code *)
    VAR optNm   : RTS.NativeString;
        suffx   : RTS.NativeString;
        fName   : RTS.NativeString;
        ignore  : BOOLEAN;
  BEGIN
    fName := MKSTR(file);
    IF main THEN
      optNm := "/exe "; suffx := ".exe";
    ELSE
      optNm := "/dll "; suffx := ".dll";
    END;
    optNm := optNm + MKSTR(optn) + " ";
    IF vbse THEN
      asm.get_StartInfo().set_CreateNoWindow(FALSE);
      asm.get_StartInfo().set_Arguments(optNm + "/nologo " + fName + ".il");
    ELSE
      asm.get_StartInfo().set_CreateNoWindow(TRUE);
      asm.get_StartInfo().set_Arguments(optNm+"/nologo /quiet "+fName+".il");
    END;
    ignore := asm.Start();
    asm.WaitForExit();
    rslt := asm.get_ExitCode();
    IF rslt = 0 THEN
      Console.WriteString("#gpcp: Created " + fName + suffx); Console.WriteLn;
    END;
  END DoAsm;

END MsilAsm.
