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

MODULE CPascalG;
  IMPORT GPCPcopyright;

CONST
  EOFSYM* = 0;  identSym* = 1;  integerSym* = 2;  realSym* = 3;
  CharConstantSym* = 4;  stringSym* = 5;  starSym* = 6;  minusSym* = 7;
  bangSym* = 8;  pointSym* = 9;  equalSym* = 10;  ARRAYSym* = 11;  
  commaSym* = 12; OFSym* = 13;  ABSTRACTSym* = 14;  EXTENSIBLESym* = 15;  
  LIMITEDSym* = 16; RECORDSym* = 17;  lparenSym* = 18;  plusSym* = 19;  
  rparenSym* = 20;  ENDSym* = 21; semicolonSym* = 22;  colonSym* = 23;  
  POINTERSym* = 24;  TOSym* = 25; PROCEDURESym* = 26;  lbrackSym* = 27;  
  rbrackSym* = 28;  uparrowSym* = 29; dollarSym* = 30;  hashSym* = 31;  
  lessSym* = 32;  lessequalSym* = 33; greaterSym* = 34;  greaterequalSym* = 35;
  INSym* = 36;  ISSym* = 37;  ORSym* = 38; slashSym* = 39;  DIVSym* = 40;  
  MODSym* = 41;  andSym* = 42;  NILSym* = 43; tildeSym* = 44;  lbraceSym* = 45;
  rbraceSym* = 46;  pointpointSym* = 47; EXITSym* = 48;  RETURNSym* = 49;  
  NEWSym* = 50;  colonequalSym* = 51;  IFSym* = 52; THENSym* = 53;  
  ELSIFSym* = 54;  ELSESym* = 55;  CASESym* = 56;  barSym* = 57; WHILESym* = 58;
  DOSym* = 59;  REPEATSym* = 60;  UNTILSym* = 61;  FORSym* = 62; BYSym* = 63;  
  LOOPSym* = 64;  WITHSym* = 65;  EMPTYSym* = 66;  BEGINSym* = 67; 
  CONSTSym* = 68;  TYPESym* = 69;  VARSym* = 70;  OUTSym* = 71;  
  IMPORTSym* = 72; MODULESym* = 73;  CLOSESym* = 74;  
  INTERFACESym* = 75;  RESCUESym* = 76; 
  STATICSym* = 77; ENUMSym* = 78; DIV0Sym* = 79; REM0Sym* = 80;
  EVENTSym* = 81; VECTORSym* = 82; NOSYM* = 83; idVariant* = 84;
  bangStrSym* = 85; 
END CPascalG.
