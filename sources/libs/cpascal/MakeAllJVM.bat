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


call cprun gpcp -special ASCII.cp
call cprun gpcp -special Console.cp
call cprun gpcp -special CPmain.cp
call cprun gpcp -special Error.cp
call cprun gpcp -special GPBinFiles.cp
call cprun gpcp -special GPFiles.cp
call cprun gpcp -special GPTextFiles.cp
call cprun gpcp -special ProgArgs.cp
call cprun gpcp -special RTS.cp
call cprun gpcp -special StdIn.cp
call cprun gpcp RealStr.cp
call cprun gpcp StringLib.cp
call cprun Browse -html -sort ASCII.cps
call cprun Browse -html -sort Console.cps
call cprun Browse -html -sort Error.cps
call cprun Browse -html -sort GPFiles.cps
call cprun Browse -html -sort GPBinFiles.cps
call cprun Browse -html -sort GPTextFiles.cps
call cprun Browse -html -sort ProgArgs.cps
call cprun Browse -html -sort RTS.cps
call cprun Browse -html -sort StdIn.cps
call cprun Browse -html -sort RealStr.cps
call cprun Browse -html -sort StringLib.cps

