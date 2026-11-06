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


(*
 *  Define various types and values
 *  for use by the other Asm* modules.
 *  This must not depend of any other
 *  gpcp module.
 *)

MODULE AsmDefinitions;
  IMPORT 
    GPCPcopyright,
    RTS,
    JL := java_lang,

    ASM := org_objectweb_asm;

  CONST versionDefault* = "7";

(* ============================================================ *)

  TYPE JlsArr* = POINTER TO ARRAY OF RTS.NativeString;
       JloArr* = POINTER TO ARRAY OF RTS.NativeObject;

(* ============================================================ *)

  PROCEDURE GetClassVersion*( IN s : ARRAY OF CHAR) : INTEGER;
  BEGIN
    IF s = "" THEN RETURN GetClassVersion( versionDefault );
    ELSIF s = "5" THEN RETURN ASM.Opcodes.V1_5;
    ELSIF s = "6" THEN RETURN ASM.Opcodes.V1_6;
    ELSIF s = "7" THEN RETURN ASM.Opcodes.V1_7;
    ELSIF s = "8" THEN RETURN ASM.Opcodes.V1_8;
    ELSE THROW( "Bad class version " + s );
    END;
  END GetClassVersion;

END AsmDefinitions.

