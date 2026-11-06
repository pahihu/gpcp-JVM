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
// Body of CPmain interface.
// This file implements the code of the CPmain.cp file.
// kjg November 1998.

package CP.CPmain;

public class CPmain
{
/*
 *  Now empty. Methods have moved to ProgArgs.
 */
	public static String[] args;

	public static void PutArgs(String[] a)
	// This method is known to the CPascal compiler, but is
	// unknown to CPascal source programs. An initialization
	// call to this method is the first thing in the synthetic
	// main method of any module which imports CPmain.
	{
	    args = a;
	}

	public static int ArgNumber()
	{
	    return args.length;
	}

	public static void GetArg(int num, char[] str)
	{
	    int i;
	    for (i = 0; i < str.length && i < args[num].length(); i++) {
		str[i] = args[num].charAt(i);
	    }
	    if (i == str.length)
		i--;
	    str[i] = '\0';
	}
} // end of public class CPmain
