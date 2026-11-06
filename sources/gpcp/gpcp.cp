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


(* ==================================================================== *)
(*									*)
(*  Driver Module for the Gardens Point Component Pascal Compiler.	*)
(*	Copyright (c) John Gough 1999, 2018.				*)
(*	This module was extensively modified from the driver		*)
(*	automatically produced by the M2 version of COCO/R, using	*)
(*	the CPascal.atg grammar used for the JVM version of GPCP.	*)
(*									*)
(* ==================================================================== *)

MODULE gpcp;
  IMPORT
	GPCPcopyright,
	CPmain,
	GPFiles,
	ProgArgs,
	Main := CPascal;

(* ==================================================================== *)

  VAR
    chr0 : CHAR;
    parN : INTEGER;
    filN : INTEGER;
    junk : INTEGER;
    argN : ARRAY 256 OF CHAR;

(* ==================================================================== *)
(*			      Main Argument Loop			*)
(* ==================================================================== *)

BEGIN
  filN := 0;
  ProgArgs.ExpandWildcards(0);
  FOR parN := 0 TO ProgArgs.ArgNumber()-1 DO
    ProgArgs.GetArg(parN, argN);
    chr0 := argN[0];
    IF (chr0 = '-') OR (chr0 = GPFiles.optChar) THEN (* option string *)
      Main.DoOption(argN$);
    ELSE
      Main.Compile(argN$, junk); INC(filN);
    END;
  END;
  IF filN = 0 THEN Main.Message("No input files specified") END;
 (*
  *  Return the result code of the final compilation
  *)
  IF junk # 0 THEN HALT(1) END;
END gpcp.

(* ==================================================================== *)
