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
(*  FileNames Module for the Gardens Point Component Pascal Compiler.	*)
(*	Copyright (c) John Gough 1999, 2000.				*)
(*									*)
(* ==================================================================== *)

MODULE FileNames;
  IMPORT GPFiles;

  TYPE
	NameString* = ARRAY 128 OF CHAR;

(* ==================================================================== *)
(*				Utilities				*)
(* ==================================================================== *)

    PROCEDURE GetBaseName*(IN in : ARRAY OF CHAR; OUT out : ARRAY OF CHAR);
      VAR sPos : INTEGER;
	  dPos : INTEGER;
	  idx  : INTEGER;
	  chr  : CHAR;
    BEGIN
     (* ------------------------- *)
     (* Index 012...      v--LEN  *)
     (*       xxxxxxxxxxxx0       *)
     (*      ^---------------sPos *)
     (*                   ^--dPos *)
     (* ------------------------- *)
     (*           before          *)
     (* ------------------------- *)
     (*                           *) 
     (*       xxx/xxxxx.xx0       *)
     (*          ^-----------sPos *)
     (*                ^-----dPos *)
     (* ------------------------- *)
     (*           after           *)
     (* ------------------------- *)
      sPos := -1;
      dPos := LEN(in$); 
      FOR idx := 0 TO dPos DO
	chr := in[idx];
	IF chr = '.' THEN 
	  dPos := idx;
	ELSIF chr = GPFiles.fileSep THEN 
	  sPos := idx;
	END;
      END;
      FOR idx := 0 TO dPos-sPos-1 DO
	out[idx] := in[idx+sPos+1];
      END;
      out[dPos-sPos] := 0X;
    END GetBaseName;

(* ==================================================================== *)

    PROCEDURE StripUpToLast*(mark : CHAR; 
			 IN  in   : ARRAY OF CHAR;
			 OUT out  : ARRAY OF CHAR);
      VAR sPos : INTEGER;
	  dPos : INTEGER;
	  idx  : INTEGER;
	  chr  : CHAR;
    BEGIN
     (* ------------------------- *)
     (* Index 012...      v--LEN  *)
     (*       xxxxxxxxxxxx0       *)
     (*      ^---------------sPos *)
     (*                   ^--dPos *)
     (* ------------------------- *)
     (*           before          *)
     (* ------------------------- *)
     (*                           *) 
     (*       xxx!xxxxx.xx0       *)
     (*          ^-----------sPos *)
     (*                ^-----dPos *)
     (* ------------------------- *)
     (*           after           *)
     (* ------------------------- *)
      sPos := -1;
      dPos := LEN(in$); 
      FOR idx := 0 TO dPos DO
	chr := in[idx];
	IF chr = '.' THEN 
	  dPos := idx;
	ELSIF chr = mark THEN 
	  sPos := idx;
	END;
      END;
      FOR idx := 0 TO dPos-sPos-1 DO
	out[idx] := in[idx+sPos+1];
      END;
      out[dPos-sPos] := 0X;
    END StripUpToLast;

(* ==================================================================== *)

    PROCEDURE AppendExt*(IN in,ext : ARRAY OF CHAR; OUT out : ARRAY OF CHAR);
      VAR pos : INTEGER;
	  idx : INTEGER;
	  chr : CHAR;
    BEGIN
      pos := LEN(in$);
      FOR idx := 0 TO pos-1 DO out[idx] := in[idx] END;
      out[pos] := ".";
      FOR idx := 0 TO LEN(ext$) DO out[idx+pos+1] := ext[idx] END;
    END AppendExt;

(* ==================================================================== *)

    PROCEDURE StripExt*(IN in : ARRAY OF CHAR; OUT out : ARRAY OF CHAR);
      VAR pos : INTEGER;
	  idx : INTEGER;
	  chr : CHAR;
    BEGIN
      pos := LEN(in$);
      FOR idx := 0 TO pos DO
	chr := in[idx];
	IF chr = '.' THEN pos := idx END;
	out[idx] := chr;
      END;
      out[pos] := 0X;
    END StripExt;

(* ==================================================================== *)
BEGIN
END FileNames.

