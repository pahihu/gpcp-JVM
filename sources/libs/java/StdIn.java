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

/*
Modified in gpcp-JVM by Andras Pahi <pahihu@gmail.com>, 2021-11-19
(commit 3ad8c16).

Why: the Java implementation of StdIn.More() always returned true (the old code
called it a temporary fix, and StdIn.cp still says "Return TRUE in gpcp v1.3!").
With redirected or piped stdin, a loop such as
  WHILE StdIn.More() DO StdIn.ReadLn(line) ... END
never terminated: after EOF readLine() returns null, ReadLn yields an empty
string, and More() stayed true.

What: set eof when readLine() returns null and let More() return rdr.ready()
(the previously commented-out line). ready() is false when no input can be read
without blocking, so loops end at EOF. The "return !eof" and old "return true"
variants are left as comments: eof is currently unused, and ready() is not an
ideal EOF test on an interactive terminal (it may be false before the first
input arrives), but it fixes redirected/piped input on the JVM.
*/

//
// Body of StdIn interface.
// This file implements the code of the StdIn.cp file.
// kjg June 2004.

package CP.StdIn;

import java.io.*;

public class StdIn
{
        private static boolean eof = false;

        private static BufferedReader rdr = 
               new BufferedReader(new InputStreamReader(System.in));

	public static void ReadLn(char[] arr) throws IOException {
            String str = rdr.readLine();
            if (str == null) {
                eof = true;
                arr[0] = '\0'; return;
            }
            int len = arr.length;
            int sLn = str.length();
            len = (sLn < len ? sLn : len-1);
            str.getChars(0, len, arr, 0);
            arr[len] = '\0';
        }

        public static char Read() throws IOException 
	{
	    return (char)rdr.read();
	}

        public static boolean More() throws IOException
	{
         // return !eof;
	 // return true;         // temporary fix until we figure out
	    return rdr.ready();  // how to get the same semantics for
	}                        // .NET and the JVM (kjg Sep. 2004)

	public static void SkipLn() throws IOException
	{
            String str = rdr.readLine(); // and discard str
	}

} // end of public class StdIn
