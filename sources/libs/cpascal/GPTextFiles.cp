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

FOREIGN MODULE GPTextFiles;

IMPORT GPFiles;

TYPE
  FILE* = POINTER TO RECORD (GPFiles.FILE) END;


PROCEDURE findLocal*(IN fileName : ARRAY OF CHAR) : FILE;
(** Find file with given name in current directory *)

PROCEDURE findOnPath*(IN pathName : ARRAY OF CHAR;
		      IN fileName : ARRAY OF CHAR) : FILE;
(** Find file with given name on path given as property *)

PROCEDURE getFullPathName*(f : FILE) : GPFiles.FileNameArray;
(** Return full name of file *)

PROCEDURE openFile*(IN fileName : ARRAY OF CHAR) : FILE;
(** Open file with given absolute name *)

PROCEDURE openFileRO*(IN fileName : ARRAY OF CHAR) : FILE;
(** Open file READ-ONLY with given absolute name *)

PROCEDURE CloseFile*(file : FILE);

PROCEDURE createFile*(IN fileName : ARRAY OF CHAR) : FILE;
(** Create file and open for reading *)

PROCEDURE createPath*(IN pathName : ARRAY OF CHAR) : FILE;
(** Create file and any necessary directories and opens file for reading *)

PROCEDURE readChar*(file : FILE) : CHAR;
 
PROCEDURE readNChars*(file : FILE; OUT buffPtr : ARRAY OF CHAR;
                     requestedChars : INTEGER) : INTEGER;
(** Return value is number actually read *)
 
PROCEDURE WriteEOL*(file : FILE);

PROCEDURE WriteChar*(file : FILE; ch : CHAR);

PROCEDURE WriteNChars*(file : FILE; IN buffPtr : ARRAY OF CHAR;
                      requestedChars : INTEGER);

END GPTextFiles.
