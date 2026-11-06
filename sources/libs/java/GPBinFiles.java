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

Why: "import CP.ProgArgs.ProgArgs.*;" is an import-on-demand from a class, not
from a package, and nothing from ProgArgs is used in GPBinFiles. It only added
an unnecessary compile-time dependency on CP.ProgArgs. The runtime sources are
compiled file by file (see MakeAll.bat); in the slimmed-down cprts.jar used for
Unix/JDK 11/17 such a dependency is unnecessary and can break the build if the
class is not visible at that compilation step.

What: the unused import is commented out. This is build cleanup, not a JVM API
requirement.
*/

//
// Body of GPFiles interface.
// This file implements the code of the GPFiles.cp file.
// dwc August 1999.


package CP.GPBinFiles;

import java.io.*;
import CP.CPJ.CPJ;
import CP.GPFiles.GPFiles.*;
// import CP.ProgArgs.ProgArgs.*;

public class GPBinFiles {

  public static int length(GPBinFiles_FILE cpf) {
    return (int) cpf.length;
  }

  public static GPBinFiles_FILE findLocal(char[] fileName) 
                                                  throws IOException {
    String currDir = System.getProperty("user.dir");
    GPBinFiles_FILE cpf = new GPBinFiles_FILE();
    cpf.f = new File(currDir, CP.CPJ.CPJ.MkStr(fileName));
    if (!cpf.f.exists()) {
      return null; 
    } else {
      cpf.rf = new RandomAccessFile(cpf.f,"r");
      cpf.length = cpf.rf.length();
      return cpf;
    }
  }
                               
  public static GPBinFiles_FILE findOnPath(char[] pathName, 
                                   char[] fileName) throws IOException { 
    //
    // Use MkStr, to trim space from end of char arrray.
    //
    String pName = CP.CPJ.CPJ.MkStr(pathName);
    String fName = CP.CPJ.CPJ.MkStr(fileName);

    String nextDir;
    String thisPath = System.getProperty(pName);
    if (thisPath == null)
	    thisPath = System.getenv(pName);
    if (thisPath == null)
	    return null;
    GPBinFiles_FILE cpf = new GPBinFiles_FILE();
    boolean found = false; 
    boolean pathFinished = false;
    int length = thisPath.length();
    int nextPathStart = -1, nextPathEnd = -1;

    while (!found && !pathFinished) {
      nextPathStart = nextPathEnd + 1;
      nextPathEnd = thisPath.indexOf(CP.GPFiles.GPFiles.pathSep,nextPathStart);
      if (nextPathEnd < 0)
	  nextPathEnd = length;
      nextDir = thisPath.substring(nextPathStart,nextPathEnd);
      cpf.f = new File(nextDir,fName);
      found = cpf.f.exists();
      pathFinished = nextPathEnd >= length; 
    } 
    if (found) {
      cpf.rf = new RandomAccessFile(cpf.f,"r");
      cpf.length = cpf.rf.length();
      return cpf;
    } else {
      return null;
    }
  }
    
  public static char[] getFullPathName(GPBinFiles_FILE cpf) {
    return cpf.f.getPath().toCharArray();
  }

  public static GPBinFiles_FILE openFile(char[] fileName)throws IOException{
    GPBinFiles_FILE cpf = new GPBinFiles_FILE();
    cpf.f = new File(CP.CPJ.CPJ.MkStr(fileName));
    if (!cpf.f.exists()) {
      return null;
    } else {
      cpf.rf = new RandomAccessFile(cpf.f,"rw");
      cpf.length = cpf.rf.length();
      return cpf;
    }
  }

  public static GPBinFiles_FILE openFileRO(char[] fileName)throws IOException{
    GPBinFiles_FILE cpf = new GPBinFiles_FILE();
    cpf.f = new File(CP.CPJ.CPJ.MkStr(fileName));
    if (!cpf.f.exists()) {
      return null;
    } else {
      cpf.rf = new RandomAccessFile(cpf.f,"r");
      cpf.length = cpf.rf.length();
      return cpf;
    }
  }

  public static void CloseFile(GPBinFiles_FILE cpf) throws IOException {
    cpf.rf.close(); 
  }

  public static GPBinFiles_FILE createFile(char[] fileName)throws IOException {
    GPBinFiles_FILE cpf = new GPBinFiles_FILE();
    cpf.f = new File(CP.CPJ.CPJ.MkStr(fileName));
    cpf.rf = new RandomAccessFile(cpf.f,"rw");
    cpf.rf.setLength(0);
    cpf.length = 0;
    //  cpf.length = cpf.rf.length();
    return cpf;
  } 

  public static GPBinFiles_FILE createPath(char[] fileName)throws IOException {
    String fName = CP.CPJ.CPJ.MkStr(fileName);
    int ix = fName.lastIndexOf(File.separatorChar);
    if (ix > 0) {
      File path = new File(fName.substring(0,ix));
      if (!path.exists()) { boolean ok = path.mkdirs(); }
    } 
    GPBinFiles_FILE cpf = new GPBinFiles_FILE();
    cpf.f = new File(fName);
    cpf.rf = new RandomAccessFile(cpf.f,"rw");
    cpf.rf.setLength(0);
    cpf.length = 0;
    //    cpf.length = cpf.rf.length();
    return cpf;
  } 
  public static boolean EOF(GPBinFiles_FILE cpf) throws IOException {
    return cpf.rf.getFilePointer() >= cpf.length;
  }

  public static int readByte(GPBinFiles_FILE cpf) throws IOException {
    try {
      return cpf.rf.readUnsignedByte();
    }
    catch (EOFException x) {
      return -1; // Compatibility with .NET version.
    }
  } 

  public static int readNBytes(GPBinFiles_FILE cpf, byte[] buff, 
                               int numBytes) throws IOException {
    return cpf.rf.read(buff,0,numBytes);
  } 

  public static void WriteByte(GPBinFiles_FILE cpf,int b) throws IOException{
    cpf.rf.write(b);
  } 

  public static void WriteNBytes(GPBinFiles_FILE cpf,byte[] buff,
                                 int numBytes) throws IOException {
    cpf.rf.write(buff,0,numBytes);
  } 

  
}
