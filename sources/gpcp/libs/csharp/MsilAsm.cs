/*
New BSD License (BSD)
Copyright (c) 2000 - 2010, K John Gough

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

* Neither the name of Queensland University of Technology nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// (* ========================================================= *)
// (**	Interface to the ILASM Byte-code assembler.		*)
// (*	K John Gough, 10th June 1999				*)
// (*	Modifications:						*)
// (*		Version for GPCP V0.3 April 2000 (kjg)		*)
// (* ========================================================= *)
// (*	The real code is in MsilAsm.cs				*)	
// (* ========================================================= *)
//
//MODULE MsilAsm;
//
//  PROCEDURE Init*(); BEGIN END Init;
//
//  PROCEDURE Assemble*(IN fil, opt : ARRAY OF CHAR; main : BOOLEAN); 
//  BEGIN END Assemble;
//
//END MsilAsm.
//
// Compile with :
//
//  $ csc /t:library /debug MsilAsm.cs
// 

using System;
using System.Text;
using System.Diagnostics;

namespace MsilAsm {

public class MsilAsm {

    private static Process asm = null;


    public static string GetDotNetRuntimeInstallDirectory() 
    {
        // Get the path to mscorlib.dll
        string s = typeof(object).Module.FullyQualifiedName;
        // Remove the file part to get the directory
        return System.IO.Directory.GetParent(s).ToString();
    }

        public static void Init() {
            if (asm == null) {
                asm = new Process();
                System.String frameworkDir = GetDotNetRuntimeInstallDirectory();
                //System.String frameworkDir = Environment.GetEnvironmentVariable("NET40", EnvironmentVariableTarget.User);
                asm.StartInfo.FileName = frameworkDir + "\\" + "ilasm";
                asm.StartInfo.CreateNoWindow = true;
                asm.StartInfo.UseShellExecute = false;
            }
        }

        private static int CPlen(char[] arr) {
            int len = arr.Length;
            for (int ix = 0; ix < len; ix++)
                if (arr[ix] == '\0')
                    return ix;
            return len;
        }

        public static void Assemble(char[] fil, char[] opt, bool hasMain) {
            int retCode;
            System.String optNm;
            System.String suffx;
            System.String fName = new String(fil, 0, CPlen(fil));
            if (hasMain) {
                optNm = "/exe ";
                suffx = ".exe";
            }
            else {
                optNm = "/dll ";
                suffx = ".dll";
            }
            optNm = optNm + new String(opt, 0, CPlen(opt)) + ' ';
            asm.StartInfo.Arguments = optNm + "/nologo /quiet " + fName + ".il";
            asm.Start();
            asm.WaitForExit();
            retCode = asm.ExitCode;
            if (retCode != 0)
                System.Console.WriteLine("#gpcp: ilasm FAILED " + retCode);
            else
                System.Console.WriteLine("#gpcp: created " + fName + suffx);
        }

        public static void DoAsm(char[] fil, char[] opt,
                    bool hasMain,
                    bool verbose,
                    ref int rslt) {
            System.String optNm;
            System.String suffx;
            System.String fName = new String(fil, 0, CPlen(fil));

            if (hasMain) {
                optNm = "/exe ";
                suffx = ".exe";
            }
            else {
                optNm = "/dll ";
                suffx = ".dll";
            }
            optNm = optNm + new String(opt, 0, CPlen(opt)) + ' ';
            if (verbose) {
                asm.StartInfo.Arguments = optNm + "/nologo " + fName + ".il";
                System.Console.WriteLine("#gpcp: Calling " + asm.StartInfo.FileName + ' ' + asm.StartInfo.Arguments);
            }
            else {
                asm.StartInfo.Arguments = optNm + "/nologo /quiet " + fName + ".il";
            }
            asm.Start();
            asm.WaitForExit();
            rslt = asm.ExitCode;
            if (rslt == 0)
                System.Console.WriteLine("#gpcp: Created " + fName + suffx);
        }


        public static void Assemble(char[] fil, bool hasMain) {
        char[] opt = {'/', 'd', 'e', 'b', 'u', 'g', '\0' };
        Assemble(fil, opt, hasMain);
    }

  }
}
