REM New BSD License (BSD)
REM Copyright (c) 2000 - 2010, K John Gough
REM
REM All rights reserved.
REM
REM Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
REM
REM * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
REM
REM * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
REM
REM * Neither the name of Queensland University of Technology nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
REM
REM THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

@echo off
REM this compiles all of the standard java-sourced libraries for GPCP
javac -d . Console.java
javac -d . CPJ.java
javac -d . CPJrts.java
javac -d . ProcKey.java
javac -d . XHR.java
javac -d . CPmain.java
javac -d . Error.java
javac -d . ProgArgs.java
javac -d . GPFiles_FILE.java
javac -d . GPFiles.java
javac -d . GPBinFiles_FILE.java
javac -d . GPBinFiles.java
javac -d . GPTextFiles_FILE.java
javac -d . GPTextFiles.java
javac -d . ProcType.java
javac -d . RTS.java
javac -d . StdIn.java
javac -d . VecBase.java
javac -d . VecChr.java
javac -d . VecI32.java
javac -d . VecI64.java
javac -d . VecR32.java
javac -d . VecR64.java
javac -d . VecBase.java
javac -d . VecRef.java
pause

