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


(* ================================================= *) 
(*   This module provides symbol tables for Browse   *)
(*   Copyright (c) John Gough 2018                   *)
(* ================================================= *)

MODULE BrowseLookup;
  IMPORT
    RTS,
    Nh := NameHash;
    

(* ============================================================ *)

  TYPE  
    DescBase* = POINTER TO ABSTRACT RECORD name* : RTS.CharOpen END;

  TYPE  (* Symbol tables are implemented by a binary tree *)
    SymInfo = POINTER TO RECORD         (* private stuff  *)
                key : INTEGER;          (* hash key value *)
                val : DescBase;         (* descriptor obj *)
                lOp : SymInfo;          (* left child     *)
                rOp : SymInfo;          (* right child    *)
              END;

    SymbolTable* = RECORD
                     root : SymInfo;
                   END;

(* ============================================================ *)
(*  Private methods of the symbol-table info-blocks             *)
(* ============================================================ *)

  PROCEDURE mkSymInfo(h : INTEGER; d : DescBase) : SymInfo;
    VAR rtrn : SymInfo;
  BEGIN
    NEW(rtrn); rtrn.key := h; rtrn.val := d; RETURN rtrn;
  END mkSymInfo;

(* -------------------------------------------- *)

  PROCEDURE (i : SymInfo)lookup(key : INTEGER) : DescBase,NEW;
  BEGIN
    IF key < i.key THEN
      IF i.lOp = NIL THEN RETURN NIL ELSE RETURN i.lOp.lookup(key) END;
    ELSIF key > i.key THEN
      IF i.rOp = NIL THEN RETURN NIL ELSE RETURN i.rOp.lookup(key) END;
    ELSE (* key must equal i.key *)
      RETURN i.val;
    END;
  END lookup;

(* -------------------------------------------- *)

  PROCEDURE (i : SymInfo)enter(h : INTEGER; d : DescBase) : BOOLEAN,NEW;
  BEGIN
    IF h < i.key THEN
      IF i.lOp = NIL THEN i.lOp := mkSymInfo(h,d); RETURN TRUE;
      ELSE RETURN i.lOp.enter(h,d);
      END;
    ELSIF h > i.key THEN
      IF i.rOp = NIL THEN i.rOp := mkSymInfo(h,d); RETURN TRUE;
      ELSE RETURN i.rOp.enter(h,d);
      END;
    ELSE (* h must equal i.key *) RETURN FALSE;
    END;
  END enter;

(* -------------------------------------------- *)

  PROCEDURE (i : SymInfo)write(h : INTEGER; d : DescBase) : SymInfo,NEW;
    VAR rtrn : SymInfo;
  BEGIN
    rtrn := i;      (* default: return self *)
    IF    h < i.key THEN i.lOp := i.lOp.write(h,d);
    ELSIF h > i.key THEN i.rOp := i.rOp.write(h,d);
    ELSE  rtrn.val := d;
    END;
    RETURN rtrn;
  END write;

(* -------------------------------------------- *)
(*              Exported Procedures             *)
(* -------------------------------------------- *)

  PROCEDURE (IN tbl : SymbolTable)lookup*(str : RTS.CharOpen) : DescBase,NEW;
  BEGIN
    IF tbl.root = NIL THEN 
      RETURN NIL;
    ELSE 
      RETURN tbl.root.lookup(Nh.enterStr(str));
    END;
  END lookup;

(* -------------------------------------------- *)

  PROCEDURE (VAR tbl : SymbolTable)Overwrite*(str : RTS.CharOpen; new : DescBase),NEW;
  BEGIN
    tbl.root := tbl.root.write(Nh.enterStr(str), new);
  END Overwrite;

(* -------------------------------------------- *)

  PROCEDURE (VAR s : SymbolTable)enter*(str : RTS.CharOpen; v : DescBase) : BOOLEAN,NEW;
  (* Enter value in SymbolTable; Return value signals successful insertion. *)
  BEGIN
    IF s.root = NIL THEN
      s.root := mkSymInfo(Nh.enterStr(str), v); RETURN TRUE;
    ELSE
      RETURN s.root.enter(Nh.enterStr(str), v);
    END;
  END enter;

(* -------------------------------------------- *)
END BrowseLookup.
(* -------------------------------------------- *)

