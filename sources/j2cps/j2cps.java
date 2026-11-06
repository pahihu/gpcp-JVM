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
Modified in gpcp-JVM by Andras Pahi <pahihu@gmail.com>, 2021-11-20
(commit 5688ea0).

Why: JDK 9+ is distributed as .jmod modules instead of rt.jar, and symbol files
for JDK 11/17 are generated with
  j2cps -dst JvmSystem -jar $JAVA_HOME/jmods/java.base.jmod
The old guard accepted only file names ending in ".jar" and exited before the
archive was opened.

What: also accept ".jmod" and update the diagnostic. No other change is needed:
JarFile can read a jmod despite its 4-byte header, and JarHandler processes the
entries like an ordinary zip (the constant-pool and package-name fixes above
make the entries usable).
*/

/**********************************************************************/
/*                      Main class for j2cps                          */
/*                                                                    */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017    */ 
/**********************************************************************/
package j2cps;

import java.io.IOException;
import java.util.jar.JarFile;
import j2cpsfiles.j2cpsfiles;

public class j2cps {

    static String pkgOrJar;
    static String argString;
    static final String versionStr = "j2cps version 1.4.07 (March 2018)";
  /**
   * Main program. Takes a package name as a parameter, produces the 
   * Component Pascal symbol file.  The class-files of the package must
   * be nested in a directory with the package name.
   * In the case of the -jar option the last argument is the path from
   * the current working directory to the target jar file.
   */
  public static void main(String args[]) { 
    int argLen = args.length;
    String argStr = null;
    boolean anonPack = false;
    boolean seenParg = false;
    MkArgString(args);
    TypeDesc.InitTypes();
    if (argLen == 0) {
	ShowHelp();
        System.exit(0);
    }
    else {
        int argIx = 0;
        argStr = args[argIx];
        while (argStr.startsWith("-")) {
            String optString = argStr.substring(1);
            /* parse options here */
            switch (argStr.charAt(1)) {
                case 'V':
                    if (optString.equalsIgnoreCase("version")) {
                        System.out.println(versionStr);
		    }
		    else if ("VERBOSE".startsWith(optString)) {
                        ClassDesc.VERBOSE = true;
                        ClassDesc.verbose = true;
                        ClassDesc.summary = true;
                    } else
                        BadOption(argStr);  
                    break;
                case 'v':
                    if ("version".equals(optString)) {
                        System.out.println(versionStr);
		    }
		    else if ("verbose".startsWith(optString)) {
                        ClassDesc.verbose = true;
                        ClassDesc.summary = true;
                        j2cpsfiles.SetVerbose( true );
                        j2cpsfiles.SetSummary( true );
                    } else
                        BadOption(argStr);
                    break;
                case 's':
                    if ("summary".startsWith(optString)) {
                        ClassDesc.summary = true;
                        j2cpsfiles.SetSummary( true );
                    } else
                        BadOption(argStr);
                    break;
                case 'd':
                    if (!"dst".startsWith(optString))
                        BadOption(argStr);
                    else if (argIx + 1 < argLen) {
                        argStr = args[++argIx];
                        j2cpsfiles.SetDstDir(argStr);
                    } else
                        System.err.println(
                            "-d option is missing symfile destination directory name");     
                    break;
                case 'p':
                    if (!"pkg".startsWith(optString))
                        BadOption(argStr);
                    else if (argIx + 1 < argLen) {
                        seenParg = true;
                        argStr = args[++argIx];
                        j2cpsfiles.SetPackageRootDir(argStr);
                    } else
                        System.err.println(
                            "-p option is missing package-root directory name");    
                    break;
                case 'h':
                case 'H':
                    if (optString.equalsIgnoreCase("help")) {
                        ShowHelp();
                    } else
                        BadOption(argStr);
                    break;
                case 'j':
                    if (optString.equalsIgnoreCase("jar")) {
                        ClassDesc.useJar = true;
                    } else
                        BadOption(argStr);
                    break;
                case 'n':
                    if (optString.equalsIgnoreCase("nocpsym")) {
                        ClassDesc.nocpsym = true;
                    } else
                        BadOption(argStr);
                    break;
                default:
                    BadOption(argStr);
                    break;
            }
            if (argIx + 1 < argLen) {
                argStr = args[++argIx];
            } else {
                System.err.println("No package-name or jar filename given, terminating");
                System.exit(1);
            }
        }
        //
        // Consistency checks ...
        //
        if (ClassDesc.useJar && seenParg) {
            System.out.println("Cannot use both -jar and -p. Ignoring -p");
        }
        if (ClassDesc.summary)
            System.out.println(argString);
        j2cpsfiles.GetPaths(ClassDesc.nocpsym);
    }
    try {
        if (ClassDesc.useJar) {
            if (ClassDesc.useJar && !argStr.toLowerCase().endsWith(".jar") & !argStr.toLowerCase().endsWith(".jmod")) {
                System.err.println("After -jar, filename must end in \".jar\" or \".jmod\"");
                System.exit(1);
            }
            pkgOrJar = "jar-file " + argStr;
            JarFile jf = new JarFile(argStr);
            JarHandler jh = new JarHandler();
            jh.ProcessJar(jf);
            PackageDesc.ProcessJarDependencies();           
        } else {
            pkgOrJar = "java package " + argStr;
            PackageDesc.MakeRootPackageDescriptor(argStr, anonPack);
            PackageDesc.ProcessPkgWorklist();
        }
        PackageDesc.WriteSymbolFiles();
    }
    catch (IOException e) {
	System.err.println("IOException occurs while reading input file.");
	System.err.println( e.getMessage() );
	System.err.println("Aborting...");
        e.printStackTrace(System.err);
	System.exit(1);
    }
  }
  
  static void MkArgString( String[] args ) {
      StringBuilder bldr = new StringBuilder( "J2cps args>");
      for (String arg : args) {
          bldr.append(' ');
          bldr.append(arg);
      }
      argString = bldr.toString();
  }

  static private void BadOption(String s) {
      System.out.println("Unknown option " + s);
  }
   
  static private void ShowHelp( ) {
        System.err.println(versionStr);
        System.err.println("Usage:");
        System.err.println("java [VM-opts] j2cps.j2cps [options] PackageNameOrJarFile");
        System.err.println("java [VM-opts] -jar j2cps.jar [options] PackageNameOrJarFile");
        System.err.println("J2cps options may be in any order.");
        System.err.println("  -d[st] dir => symbol file destination directory");
        System.err.println("  -p[kg] dir => package-root directory");
        System.err.println("  -jar       => process the named jar file");
        System.err.println("  -s[ummary] => summary of progress");
        System.err.println("  -v[erbose] => verbose diagnostic messages");
        System.err.println("  -version   => show version string");
        System.err.println("  -nocpsym   => only use sym-files from destination,");
        System.err.println("                (overrides any CPSYM path setting)");
  }
}

