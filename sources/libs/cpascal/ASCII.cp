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

(** This is the dummy module that sits in the runtime system, 
  * or will do if it ever gets a body.
  *
  * Version:	19 May      2001 (kjg).
  *)

SYSTEM MODULE ASCII;

  CONST
    NUL* = 00X;
    SOH* = 01X;
    STX* = 02X;
    ETX* = 03X;
    EOT* = 04X;
    ENQ* = 05X;
    ACK* = 06X;
    BEL* = 07X;
    BS*  = 08X;		(* backspace character *)
    HT*  = 09X;		(* horizontal tab character *)
    LF*  = 0AX;		(* line feed character *)
    VT*  = 0BX;
    FF*  = 0CX;
    CR*  = 0DX; 	(* carriage return character *)
    SO*  = 0EX;
    SI*  = 0FX;
    DLE* = 10X;
    DC1* = 11X;
    DC2* = 12X;
    DC3* = 13X;
    DC4* = 14X;
    NAK* = 15X;
    SYN* = 16X;
    ETB* = 17X;
    CAN* = 18X;
    EM*  = 19X;
    SUB* = 1AX;
    ESC* = 1BX;		(* escape character *)
    FS*  = 1CX;
    GS*  = 1DX;
    RS*  = 1EX;
    US*  = 1FX;
    SP*  = 20X;		(* space character  *)
    DEL* = 7FX;		(* delete character *)

END ASCII.
