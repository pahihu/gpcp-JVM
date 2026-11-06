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

FOREIGN MODULE GPBinFiles;

IMPORT GPFiles;

TYPE
  FILE* = POINTER TO RECORD (GPFiles.FILE) END;


PROCEDURE length*(f : FILE) : INTEGER;

PROCEDURE findLocal*(IN fileName : ARRAY OF CHAR) : FILE;

PROCEDURE findOnPath*(IN pathName : ARRAY OF CHAR;
		      IN fileName : ARRAY OF CHAR) : FILE;

PROCEDURE getFullPathName*(f : FILE) : GPFiles.FileNameArray;

PROCEDURE openFile*(IN fileName : ARRAY OF CHAR) : FILE;
PROCEDURE openFileRO*(IN fileName : ARRAY OF CHAR) : FILE;

PROCEDURE CloseFile*(file : FILE);

PROCEDURE createFile*(IN fileName : ARRAY OF CHAR) : FILE;

PROCEDURE createPath*(IN pathName : ARRAY OF CHAR) : FILE;

PROCEDURE EOF*(file : FILE) : BOOLEAN;

PROCEDURE readByte*(file : FILE) : INTEGER;
 
PROCEDURE readNBytes*(file : FILE; OUT buffPtr : ARRAY OF UBYTE;
                     requestedBytes : INTEGER) : INTEGER;
 
PROCEDURE WriteByte*(file : FILE; b : INTEGER);

PROCEDURE WriteNBytes*(file : FILE; IN buffPtr : ARRAY OF UBYTE;
                       requestedBytes : INTEGER);

END GPBinFiles.
