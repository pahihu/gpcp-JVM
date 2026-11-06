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
 *  (c) copyright John Gough, 2012-2017   
 */
package j2cps;

import java.io.InputStream;
import java.io.IOException;
//import java.util.HashMap;
//import java.util.ArrayList;
import java.util.Enumeration;
import java.util.jar.JarFile;
import java.util.jar.JarEntry;

/**
 *
 * @author john
 */
public class JarHandler {
    
    public JarHandler( ) { }
    
    public void ProcessJar( JarFile jf ){
        System.out.printf("INFO: opened jar file <%s>\n", jf.getName());
        Enumeration<JarEntry> entries = jf.entries();
        String classFileName;
        String className;
        while (entries.hasMoreElements()) {
            JarEntry entry = entries.nextElement();
            classFileName = entry.getName();
            //System.out.println(entryName);
            if (classFileName.toLowerCase().endsWith(".class")) {
                className = classFileName.substring(0, classFileName.length() - 6);
                try {
                    ClassDesc desc = ClassDesc.MakeNewClassDesc(className, null);
                    desc.parentPkg.myClasses.add(desc);
                    desc.parentPkg.processed = true;
                    InputStream classStream = jf.getInputStream( entry );
                    boolean ok = desc.ReadJarClassFile(classStream);
                    if (ClassDesc.verbose)
                        System.out.printf( "Read jar class %s ... %s\n", className, (ok ? "OK" : "error"));
                } catch (IOException x) {
                    // Message
                    System.err.println( "ProcessJar threw IOException");
                    System.err.println( x.getMessage() );
                    // x.printStackTrace();
                    System.exit(1);                    
                }
            }
        }
        //
        //  At this point all the class files in the jar have
        //  been processed, and all packages listed in the todo
        //  collection. However, dependent packages have not been
        //  processed. 
        //
    } 
}
