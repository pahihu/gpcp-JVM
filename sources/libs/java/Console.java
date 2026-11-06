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
// Body of Console interface.
// This file implements the code of the Console.cp file.
// kjg November 1998.

package CP.Console;

public class Console
{
	public static void WriteLn()
	{
	    System.out.println();
	}

	public static void Write(char ch)
	{
	    System.out.print(ch);
	}

	private static char[] strRep(int val)
	{
	    if (val < 0) { // ==> must be minInt
		char[] min = {' ',' ','2','1','4','7','4','8','3','6','4','8'};
		return min;
	    }

	    char[] str = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	    str[11] = (char) (val % 10 + (int) '0'); val = val / 10;
	    for (int i = 10; val != 0; i--) {
		str[i] = (char) (val % 10 + (int) '0'); val = val / 10;
	    }
	    return str;
	}

	public static void WriteInt(int val, int fwd)
	{
	    char[] str = (val >= 0 ? strRep(val) : strRep(-val));

	    int blank;
	    for (blank = 0; str[blank] == ' '; blank++)
		;
	    if (val < 0) {
		str[blank-1] = '-'; blank--;
	    }
	    // format ...
	    // 01...............901
	    // _________xxxxxxxxxxx
	    // <-blank->< 12-blank>
	    //     <-----fwd------>
	    if (fwd == 0) // magic case, put out exactly one blank
		System.out.print(new String(str, blank-1, 13-blank));
	    else if (fwd < (12-blank))
		System.out.print(new String(str, blank, 12-blank));
	    else if (fwd <= 12)
		System.out.print(new String(str, 12-fwd, fwd));
	    else { // fwd > 12
		for (int i = fwd-12; i > 0; i--)
		    System.out.print(" ");
		System.out.print(new String(str));
	    }
	}

	public static void WriteHex(int val, int wid)
	{
	    char[] str = new char[9];
	    String jls;
	    int j;		// index of last blank
	    int i = 8;
	    do {
		int dig = val & 0xF;
		val = val >>> 4;
		if (dig >= 10)
		    str[i] = (char) (dig + ((int) 'A' - 10));
		else
		    str[i] = (char) (dig + (int) '0');
		i--;
	    } while (val != 0);
	    j = i;
	    while (i >= 0) {
		str[i] = ' '; i--;
	    }
	    if (wid == 0)	// special case, exactly one blank
		jls = new String(str, j, 9-j);
	    else if (wid < (8-j))
		jls = new String(str, j+1, 8-j);
	    else if (wid <= 9)
		jls = new String(str, 9-wid, wid);
	    else {
		for (i = wid-9; i > 0; i--)
			System.out.print(" ");
		jls = new String(str);
	    }
	    System.out.print(jls);
	}


	public static void WriteString(char[] str)
	{
	   int len = str.length;
	   for (int i = 0; i < len && str[i] != '\0'; i++)
		System.out.print(str[i]);
	}


} // end of public class Console
