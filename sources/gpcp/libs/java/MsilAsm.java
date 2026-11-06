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
// (*	The real code is in MsilAsm.cs or MsilAsm.java          *)
// (* ========================================================= *)
//
//MODULE MsilAsm;
//
//  PROCEDURE Init*(); BEGIN END Init;
//
//  PROCEDURE Assemble*(IN fil,opt : ARRAY OF CHAR; main : BOOLEAN); 
//  BEGIN END Assemble;
//
//  PROCEDURE DoAsm*(IN fil,opt : ARRAY OF CHAR; 
//                    main,vbse : BOOLEAN;
//                     OUT rslt : INTEGER); 
//  BEGIN END Assemble;
//
//END MsilAsm.
// 
//  NOTES:
//    This code assumes that ilasm.exe is visible on the path.
//    If the DoAsm call fails with a "cannot find ilasm" error
//    then you will have to locate it in the file system.
//    The program exists if you have the .NET JDK (instead of
//    just the runtime), or if you have any recent Visual Studio
//    releases. 
//    On Windows try searching C:\Windows\Microsoft.NET\Framework
//    and choose the latest version if there are several.
//    My ilasm.exe is in directory -
//        C:\WINDOWS\Microsoft.NET\Framework\v4.0.30319
//
package CP.MsilAsm;

public class MsilAsm {

    public static void Init() {
	    // empty
    }

    /**
     *  Copies the characters from the stream 
     *  <code>strm</code> to System.out, with every 
     *  line prefixed by the string "#ilasm".
     *  @throws IOException
     */
    static void CopyStream(java.io.InputStream strm) 
	    throws java.io.IOException {
        int chr;
        String prefix = "#ilasm: ";
        System.out.print(prefix);
        while ((chr = strm.read()) != -1) {
            System.out.print((char)chr);
            if (chr == (int)'\n')
                System.out.print(prefix);
        }
        System.out.println();
    }

    public static void Assemble(char[] fil, 
                                char[] opt, 
                                boolean main) {
	    // empty
    }

    public static int DoAsm(char[] fil,   // Command name 
                            char[] opt,   // Options, usually /debug
                            boolean main, // true ==> EXE, else DLL
                            boolean vrbs) // true ==> -verbose flag set
    {
        int rslt = 0;
        java.util.ArrayList<String> cmdList = new java.util.ArrayList<String>();
	//
	// Arg[0] is the command name
	//
        cmdList.add("ilasm");
        cmdList.add(vrbs ? "/nologo" : "/quiet");
        cmdList.add(main ? "/exe" : "/dll");
	//
	//  Now the rest of the user-supplied args
	//
        String[] args = new String(opt).trim().split(" ");
        for (int i = 0; i < args.length; i++)
            if (args[i].length() > 0)
                cmdList.add(args[i]);
        //
	// Now add the IL source file name
	//
        String fName = new String(fil).trim();
        cmdList.add(fName + ".il");

        String sffx = (main ? ".exe" : ".dll");
        // 
        if (vrbs) {
            System.out.print("#gpcp: MsilAsm spawning -\n       ");
            for (int i = 0; i < cmdList.size(); i++)
                 System.out.print(cmdList.get(i) + " ");
            System.out.println();
        }
        //
        try {
            Process proc = 
                new ProcessBuilder(cmdList).redirectErrorStream(true).start();
	    // Write output of process to System.out
            CopyStream(proc.getInputStream());
	    // wait for process to exit.
            rslt = proc.waitFor();
        }
        catch (Exception exc) {
            rslt = 2;
        }
        if (rslt == 0)
	    System.out.println("#gpcp: Created " + fName + (main ? ".exe" : ".dll"));
        else
	    System.out.println("#gpcp: ILASM FAILED");
        return rslt;
    }
}

