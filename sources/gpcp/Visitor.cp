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
(*                                                                      *)
(*  Visitor pattern for the Gardens Point Component Pascal Compiler.    *)
(*  This module defines various extensions of type Symbols.SymForAll    *)
(*  Copyright (c) John Gough 1999, 2000.                                *)
(*                                                                      *)
(* ==================================================================== *)

MODULE Visitor;

  IMPORT
        GPCPcopyright,
        Console,
        Symbols,
        CPascalS,
        LitValue,
        Id := IdDesc,
        Ty := TypeDesc,
        NameHash;

(* ============================================================ *)

  TYPE
    Resolver* = POINTER TO RECORD (Symbols.SymForAll) END;

(* -------------------------------------------- *)

  TYPE
    ImplementedCheck* = POINTER TO RECORD (Symbols.SymForAll) END;

(* -------------------------------------------- *)

  TYPE
    TypeEraser* = POINTER TO RECORD (Symbols.SymForAll) END;

(* -------------------------------------------- *)

  TYPE
    Accumulator* = POINTER TO RECORD (Symbols.SymForAll)
         missing  : Symbols.SymbolTable;
         recordTb : Ty.Record;
         isIntrfc : BOOLEAN;
       END;

(* ============================================================ *)

  PROCEDURE newAccumulator(target : Ty.Record) : Accumulator;
  (** Create a new symbol table and add to it all of the abstract *)
  (*  methods which are not concrete in the target scope space.   *)
    VAR tmp : Accumulator;
  BEGIN
    NEW(tmp);
    tmp.recordTb := target;
    tmp.isIntrfc := FALSE;  (* not an interface *)
    RETURN tmp;
  END newAccumulator;

 (* --------------------------- *)

  PROCEDURE newInterfaceCheck(target : Ty.Record) : Accumulator;
  (** Create a new symbol table and add to it all of the abstract *)
  (*  methods which are not concrete in the target scope space.   *)
    VAR tmp : Accumulator;
  BEGIN
    NEW(tmp);
    tmp.recordTb := target;
    tmp.isIntrfc := TRUE; (* is an interface *)
    RETURN tmp;
  END newInterfaceCheck;

 (* --------------------------- *)

  PROCEDURE (sfa : Accumulator)Op*(id : Symbols.Idnt);
    VAR anyId : Symbols.Idnt;
        pType : Ty.Procedure;
        junk  : BOOLEAN;
  BEGIN
    IF id.isAbstract() THEN
     (*
      *  Lookup the id in the original record name-scope
      *  If id implements some interface method, we must
      *  force it to be virtual by getting rid of newBit.
      *)
      anyId := sfa.recordTb.bindField(id.hash);
      IF (anyId = NIL) OR anyId.isAbstract() THEN
        junk := sfa.missing.enter(id.hash, id);
      ELSIF sfa.isIntrfc & (anyId.kind = Id.conMth) THEN
        EXCL(anyId(Id.MthId).mthAtt, Id.newBit);
        pType := id.type(Ty.Procedure);
        pType.CheckCovariance(anyId);
        IF id.vMod # anyId.vMod THEN anyId.IdError(163) END;
        IF id(Id.Procs).prcNm # NIL THEN
            anyId(Id.Procs).prcNm := id(Id.Procs).prcNm END;
      END;
    END;
  END Op;

(* -------------------------------------------- *)

  PROCEDURE newImplementedCheck*() : ImplementedCheck;
    VAR tmp : ImplementedCheck;
  BEGIN NEW(tmp); RETURN tmp END newImplementedCheck;

 (* --------------------------- *)

  PROCEDURE (sfa : ImplementedCheck)Op*(id : Symbols.Idnt);
    VAR acc : Accumulator;
        rTp : Ty.Record;
        nTp : Ty.Record;
        bTp : Symbols.Type;
        idx : INTEGER;
   (* ----------------------------------------- *)
    PROCEDURE InterfaceIterate(r : Ty.Record;
             a : Accumulator);
      VAR i : INTEGER;
          x : Ty.Record;
    BEGIN
      FOR i := 0 TO r.interfaces.tide - 1 DO
        x := r.interfaces.a[i].boundRecTp()(Ty.Record);
        x.symTb.Apply(a);
        InterfaceIterate(x, a); (* recurse to inherited interfaces *)
      END;
    END InterfaceIterate;
   (* ----------------------------------------- *)
  BEGIN
    IF id.kind = Id.typId THEN
      rTp := id.type.boundRecTp()(Ty.Record);
      IF (rTp # NIL) &      (* ==> this is a record type  *)
         ~rTp.isAbsRecType() &    (* ==> this rec is NOT abstract *)
         ~rTp.isImportedType() &  (* ==> this rec is NOT imported *)
         (rTp.baseTp # NIL) THEN  (* ==> this extends some type   *)
        bTp := rTp.baseTp;
        IF bTp.isAbsRecType() THEN  (* ==> and base _is_ abstract.  *)
         (*
          *  This is a concrete record extending an abstract record.
          *  By now, all inherited abstract methods must have been
          *  resolved to concrete methods.  Traverse up the base
          *  hierarchy accumulating unimplemented methods.
          *)
          acc := newAccumulator(rTp);
          REPEAT
            nTp := bTp(Ty.Record);  (* guaranteed for first time  *)
            bTp := nTp.baseTp;
            nTp.symTb.Apply(acc);
          UNTIL (bTp = NIL) OR bTp.isBaseType();
         (*
          *  Now we turn the missing table into a list.
          *)
          IF ~acc.missing.isEmpty() THEN
            CPascalS.SemError.RepSt1(121, Symbols.dumpList(acc.missing),
            id.token.lin, id.token.col);
          END;
        END;
        IF rTp.interfaces.tide > 0 THEN
         (*
          *   The record rTp claims to implement interfaces.
          *   We must check conformance to the contract.
          *)
          acc := newInterfaceCheck(rTp);
          InterfaceIterate(rTp, acc);
         (*
          *  Now we turn the missing table into a list.
          *)
          IF ~acc.missing.isEmpty() THEN
            CPascalS.SemError.RepSt1(159, Symbols.dumpList(acc.missing),
            id.token.lin, id.token.col);
          END;
        END;
      END;
    END;
  END Op;

(* -------------------------------------------- *)

  PROCEDURE newResolver*() : Resolver;
    VAR tmp : Resolver;
  BEGIN
    NEW(tmp);
    RETURN tmp;
  END newResolver;

 (* --------------------------- *)

  PROCEDURE (sfa : Resolver)Op*(id : Symbols.Idnt);
    VAR idTp : Symbols.Type;
  BEGIN
    IF (id.kind = Id.typId) OR (id.kind = Id.varId) THEN
      idTp := id.type;
      IF idTp # NIL THEN
        idTp := idTp.resolve(1);
(* ------------------------------------------------- *
 *      IF idTp # NIL THEN
 *        WITH idTp : Ty.Array DO
 *           IF idTp.isOpenArrType() THEN id.IdError(67) END;
 *        | idTp : Ty.Record DO
 *           IF id.kind = Id.varId THEN idTp.InstantiateCheck(id.token) END;
 *        ELSE
 *        END;
 *      END;
 * ------------------------------------------------- *)
        IF (idTp # NIL) & (id.kind = Id.varId) THEN
          WITH idTp : Ty.Array DO (* only for varIds, kjg 2004 *)
             IF idTp.isOpenArrType() THEN id.IdError(67) END;
          | idTp : Ty.Record DO
             idTp.InstantiateCheck(id.token);
          ELSE
          END;
        END;
(* ------------------------------------------------- *)
      END;
      id.type := idTp;
    END;
  END Op;

 (* --------------------------- *)

  PROCEDURE newTypeEraser*() : TypeEraser;
    VAR tmp : TypeEraser;
  BEGIN
    NEW(tmp);
    RETURN tmp;
  END newTypeEraser;

 (* --------------------------- *)

  PROCEDURE (sfa : TypeEraser)Op*(id : Symbols.Idnt);
  (* Erases any compound types found in the symbol table. These
   *  are converted to their implementation types *)
    VAR idTp : Symbols.Type;
        ct   : Ty.Record;
  BEGIN
    IF id.type # NIL THEN
      id.type := id.type.TypeErase();
    END;
  END Op;

(* ============================================================ *)
END Visitor.  (* ============================================== *)
(* ============================================================ *)

