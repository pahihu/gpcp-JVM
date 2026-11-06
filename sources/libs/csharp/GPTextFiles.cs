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

/* ------------------------------------------------------------	*/
//
// Body of GPTextFiles interface.
// This file implements the code of the GPTextFiles.cp file.
// dwc August 1999,  C# version May 2000, kjg.
// dwc May 2001.  Version for Beta-2 libraries.
//
// Compile with : csc /t:library /r:GPFiles.dll GPTextFiles.cs
//
/* ------------------------------------------------------------	*/
using System;
using GPFiles;

/* ------------------------------------------------------------	*/

namespace GPTextFiles {
public class GPTextFiles 
{
  /* ----------------------------------	*/

  private static System.String mkStr(char[] arr) {
    int  ix = 0;
    char ch;
    do {
	ch = arr[ix]; ix++;
    } while (ch != '\0');
    return new System.String(arr,0,ix-1);
  }

  /* ----------------------------------	*/

  private static FILE open(System.String name) {
    try {
      FILE cpf = new FILE();
      cpf.path = name;
      System.IO.FileStream fStr = 
                           System.IO.File.Open(name, System.IO.FileMode.Open);
      cpf.strR = new System.IO.StreamReader(fStr);
      return cpf;
    } catch {
      return null;
    }
  }
                               
  private static FILE openRead(System.String name) {
    try {
      FILE cpf = new FILE();
      cpf.path = name;
      System.IO.FileStream fStr = System.IO.File.OpenRead(name);
      cpf.strR = new System.IO.StreamReader(fStr);
      return cpf;
    } catch {
      return null;
    }
  }
                               
  /* ----------------------------------	*/

  public static FILE findLocal(char[] fileName) 
  {
    return open(mkStr(fileName));
  }

  /* ----------------------------------	*/

  public static FILE findOnPath(
			char[] pathName, char[] fileName) 
  {
    //
    // Use mkStr, to trim space from end of char arrray.
    //
    System.String pName = mkStr(pathName);
    System.String fName = mkStr(fileName);
    System.String nName = "";

    System.String nextDir;
    System.String thisPath = System.Environment.GetEnvironmentVariable(pName);
//
//  System.Console.WriteLine(pName);
//  System.Console.WriteLine(thisPath);
//
    FILE cpf = new FILE();
    bool found = false; 
    bool pathFinished = false;
    int length = thisPath.Length;
    int nextLength;
    int nextPathStart;
    int nextPathEnd   = -1;

    while (!found && !pathFinished) {
      nextPathStart = nextPathEnd + 1;
      nextPathEnd   = thisPath.IndexOf(GPFiles.GPFiles.pathSep, nextPathStart);
      if (nextPathEnd < 0)
	  nextPathEnd = length;
      nextLength    = nextPathEnd - nextPathStart;
      nextDir = thisPath.Substring(nextPathStart, nextLength);
      nName = nextDir + GPFiles.GPFiles.fileSep + fName;
      found = System.IO.File.Exists(nName);
      pathFinished = nextPathEnd >= length; 
    } 
    if (found) {
        return open(nName);
    } else
        return null;
  }
   
  /* ----------------------------------	*/

  public static char[] getFullPathName(FILE cpf) {
    return cpf.path.ToCharArray();
  }

  /* ----------------------------------	*/

  public static FILE openFile(char[] fileName) 
  {
    return open(mkStr(fileName));
  }

  /* ----------------------------------	*/

  public static FILE openFileRO(char[] fileName) 
  {
    return openRead(mkStr(fileName));
  }

  /* ----------------------------------	*/

  public static void CloseFile(FILE cpf) 
  {
    if (cpf.strW != null) {
      cpf.strW.Close();	// Close does automatic Flush()
    }
    if (cpf.strR != null) {
      cpf.strR.Close();
    }
  }

  /* ----------------------------------	*/

  public static FILE createFile(char[] fileName) 
  {
    FILE cpf = new FILE();
    try {
      System.String name = mkStr(fileName);
      System.IO.FileStream fStr = System.IO.File.Create(name);
      cpf.path = name;
	cpf.strW = new System.IO.StreamWriter(fStr);
	return cpf;
    } catch {
	return null;
    }
  } 

  /* ---------------------------------- */

  public static FILE createPath(char[] fileName)
  {
    System.String fName = mkStr(fileName);
    try {
      int ix = fName.LastIndexOf(GPFiles.GPFiles.fileSep);
      if (ix > 0) {
        System.String path = fName.Substring(0,ix);
        if (!System.IO.Directory.Exists(path)) {
          System.IO.DirectoryInfo junk = System.IO.Directory.CreateDirectory(path);
        }
      }
      FILE cpf = new FILE();
      cpf.path = fName;
      System.IO.FileStream fStr = System.IO.File.Create(fName);
      cpf.strW = new System.IO.StreamWriter(fStr);
      return cpf;
    } catch {
        return null;
    }
  }

  /* ----------------------------------	*/

  public static char readChar(FILE cpf)
  {
    if (cpf.strR != null) {
	int chr = cpf.strR.Read();
	if (chr == -1)
	    return (char) 0;
	else
	    return (char) chr;
    } else
	throw new System.Exception("File not open for reading");
  } 

  /* ----------------------------------	*/

  public static int readNChars(
			FILE cpf, 
			char[] buff, 
			int    want) 
  {
    return cpf.strR.Read(buff,0,want);
  } 

  /* ----------------------------------	*/

  public static void WriteChar(FILE cpf, char ch) 
  {
    if (cpf.strW != null) {
	cpf.strW.Write(ch);
    } else
	throw new System.Exception("File not open for writing");
  } 

  /* ----------------------------------	*/

  public static void WriteEOL(FILE cpf) 
  {
    if (cpf.strW != null) {
	cpf.strW.Write(Environment.NewLine);
    } else
	throw new System.Exception("File not open for writing");
  } 

  /* ----------------------------------	*/

  public static void WriteNChars(
			FILE cpf, 
			char[] buff, 
			int    want)
  {
    if (cpf.strW != null) {
	cpf.strW.Write(buff, 0, want);
    } else
	throw new System.Exception("File not open for writing");
  } 
}	// end of class GPTextFiles

/* ------------------------------------------------------------ */
/*		File-descriptor for GPTextFiles			*/
/* ------------------------------------------------------------ */

  public class FILE : GPFiles.FILE
  {
     public System.IO.StreamReader strR;
     public System.IO.StreamWriter strW;
  }	// end of class FILE

/* ------------------------------------------------------------ */
} // end of GPTextFiles.
/* ------------------------------------------------------------ */

