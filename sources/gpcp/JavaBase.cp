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
(*  JavaBase is the abstract class for java byte code emitters.	*)
(*  The method Target.Select(mod, <name>) will allocate a 	*)
(*  ClassMaker  object of an appropriate kind, and will call	*)
(*	classMaker.Emit()					*)
(*  Copyright (c) John Gough 1999, 2000. 			*)
(*  Modified DWC September,2000		 			*)
(* ============================================================ *)

MODULE JavaBase;

  IMPORT 
	GPCPcopyright,
	Console,
	Ty := TypeDesc,
	ClassMaker;
	

(* ============================================================ *)

  TYPE
    ClassEmitter* = POINTER TO ABSTRACT 
 		      RECORD (ClassMaker.ClassEmitter) END;

(* ============================================================ *)
(*  Not very elegant, but we need to get at the worklist from   *)
(*  inside static procedures in JsmnUtil.			*)
(* ============================================================ *)

  VAR worklist*   : ClassEmitter;

  PROCEDURE (list : ClassEmitter)AddNewRecEmitter*(rec : Ty.Record),NEW,EMPTY;
  PROCEDURE (list : ClassEmitter)AddNewProcTypeEmitter*(prc : Ty.Procedure),NEW,EMPTY;

(* ============================================================ *)
END JavaBase.
(* ============================================================ *)
