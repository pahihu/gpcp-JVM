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

/* ------------------------------------------------------------ */
// Body of GPFiles interface.
// This file implements the code of the GPFiles.cp file.
// dwc August 1999. COOL version kjg May 2000
// kjg September 2000.  Stripped version as abstract base class.
// kjg March 2001.  Version for Beta-2 libraries.
/* ------------------------------------------------------------ */

namespace GPFiles {
public abstract class GPFiles {

  public static char pathSep = ';';
  public static char fileSep = '\\';
  public static char optChar = '/';

  /* ----------------------------------	*/

  private static System.String mkStr(char[] arr) {
    int  ix = 0;
    char ch;
    do {
	  ch = arr[ix]; ix++;
    } while (ch != '\0');
    return new System.String(arr,0,ix-1);
  }

  private static char[] mkArr(System.String str) {
    char[] rslt = new char[str.Length + 1];
    str.CopyTo(0, rslt, 0, str.Length);
    rslt[str.Length] = '\0';
    return rslt;
  }

  /* ----------------------------------	*/

  public static bool isOlder(FILE first, FILE second) {
	int comp = System.DateTime.Compare(
		     System.IO.File.GetLastWriteTime(first.path),
		     System.IO.File.GetLastWriteTime(second.path)
		);
	return comp == -1;
    }

  public static void MakeDirectory(char[] dirName) {
	System.String path = mkStr(dirName);
        System.IO.Directory.CreateDirectory(path);
    }

  public static char[] CurrentDirectory() {
        return mkArr(System.IO.Directory.GetCurrentDirectory());
  }
  
  public static bool exists(char[] filName) {
	System.String path  = mkStr(filName);
	return System.IO.File.Exists(path);
    }

   public static char[][] FileList(char[] dirPath) {
       string dirStr = mkStr(dirPath);
       string[] files = System.IO.Directory.GetFiles(dirStr);
       if (files == null || files.Length ==0) return null;
       else {
           char[][] rslt = new char[files.Length][];
           for (int i = 0; i < files.Length; i++)
               rslt[i] = mkArr(System.IO.Path.GetFileName(files[i]));
	   return rslt;
       }
   } 
  } // end of class GPFiles

/* ------------------------------------------------------------ */

public abstract class FILE {
	public System.String path;
  }  // end of class GPFiles.FILE

/* ------------------------------------------------------------ */
}  // end of NameSpace GPFiles
/* ------------------------------------------------------------ */

