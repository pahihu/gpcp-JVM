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

//
// Body of ProgArgs interface.
// This file implements the code of the ProgArgs.cp file.
// kjg December 1999.
//
// The reason that this module is implemented as a Java class is
// that the name CPmain has special meaning to the compiler, so
// it must be imported secretly in the implementation.
//

package CP.ProgArgs;
import  CP.CPmain.CPmain;
import  java.io.File;
import  java.nio.file.*;
import  java.util.ArrayList;

public class ProgArgs
{
    public static int ArgNumber()
    {
        if (CP.CPmain.CPmain.args == null)
            return 0;
        else
            return CP.CPmain.CPmain.args.length;
    }

    public static void GetArg(int num, char[] str)
    {
        int i;
        if (CP.CPmain.CPmain.args == null) {
            str[0] = '\0';
        } else {
            for (i = 0; 
                i < str.length && i < CP.CPmain.CPmain.args[num].length();
                i++) {
                str[i] = CP.CPmain.CPmain.args[num].charAt(i);
            }
        if (i == str.length)
            i--;
        str[i] = '\0';
        }
    }

    public static void GetEnvVar(char[] ss, char[] ds) 
    {
        String path = CP.CPJ.CPJ.MkStr(ss);
        //
        //  getenv was deprecated between jave 1.1 and SE 5 (!)
        //
        String valu = System.getProperty(path);
        if (valu == null) // Try getenv instead
            valu = System.getenv(path);
            int i;
            for (i = 0; 
                 i < valu.length() && i < ds.length;
                 i++) {
                ds[i] = valu.charAt(i);
            }
            if (i == ds.length)
                i--;
            ds[i] = '\0';
        }

    public static void ExpandWildcards(int argsToSkip) {
        //
        // The Java launcher expands wildcards, but only
        // for simple filenames in the current directory.
        // 
        try {
            CP.CPmain.CPmain.args = ExpandArgs(CP.CPmain.CPmain.args, argsToSkip);
        } catch (Exception x) {
            System.err.println(x.toString());
        }
    }

    private static boolean needsExpansion(String arg) {
	return (arg.contains("*") || arg.contains("?"));
    }

    
    private static String[] ExpandArgs(String[] args, int first) throws Exception {
        ArrayList<String> list = new ArrayList<String>();
        for (int i = 0; i < args.length; i++) {
            String argS = args[i];
            if (i < first || argS.charAt(0) == '-' || !needsExpansion(argS)) {
                list.add(argS);
            } else {
                File argF = new File(args[i]);
                File parent = argF.getParentFile();
                String pattern = argF.getName();
                boolean implicitParent = (parent == null);
                if (implicitParent)
                    parent = new File(".");
                try (DirectoryStream<Path> stream = 
                        Files.newDirectoryStream(parent.toPath(), pattern)) {
                    for (Path entry: stream) {
                        if (implicitParent)
                            list.add(entry.toFile().getName());
                        else
                            list.add(entry.toString());
                    }
                } catch (DirectoryIteratorException x) {
                        throw x.getCause();
                }
            }
        }
        return list.toArray(new String[0]);
    }

} // end of public class ProgArgs
