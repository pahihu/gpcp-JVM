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
(*  Target is the module which selects the target ClassMaker.	*)
(*  Copyright (c) John Gough 1999, 2000.			*)
(* ============================================================ *)

MODULE Target; 

  IMPORT 
	GPCPcopyright,
	Symbols,
	CompState,
	ClassMaker,
	JavaMaker,
	MsilMaker,
	IdDesc;

(* ============================================================ *)

  VAR
    maker : ClassMaker.ClassEmitter;
    assmb : ClassMaker.Assembler;

(* ============================================================ *)

  PROCEDURE Select*(mod : IdDesc.BlkId; 
                 IN str : ARRAY OF CHAR);
  BEGIN
    IF str = "jvm" THEN
      maker := JavaMaker.newJavaEmitter(mod);
      assmb := JavaMaker.newJavaAsm();
      Symbols.SetTargetIsNET(FALSE);
    ELSIF str = "net" THEN
      maker := MsilMaker.newMsilEmitter(mod);
      assmb := MsilMaker.newMsilAsm();
      Symbols.SetTargetIsNET(TRUE);
    ELSE
      CompState.Message("Unknown emitter name <" + str + ">");
    END;
    CompState.SetEmitter(maker);
  END Select;

(* ============================================================ *)

  PROCEDURE Init*();
  BEGIN
    maker.Init();
  END Init;

  PROCEDURE Emit*();
  BEGIN
    maker.Emit();
  END Emit;

  PROCEDURE Assemble*();
  BEGIN
    assmb.Assemble();
  END Assemble;

(* ============================================================ *)
END Target.
(* ============================================================ *)
