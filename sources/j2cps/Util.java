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
 * (c) copyright John Gough, 2016-2017
 */
package j2cps;

// import java.util.function.Predicate;

/**
 *
 * @author john
 */
public class Util {
    //
    // All these constants are package private
    //
    static final int PRISTINE = 0;
    static final int ONLIST   = 0x1;
    static final int ONTODO   = 0x2;
    static final int ONSYMS   = 0x4;
    static final int FROMJAR  = 0x8;
    static final int FROMCLS  = 0x10;
    static final int APINEEDS = 0x20;
    static final int FOUNDCPS = 0x40;
    static final int CURRENT  = 0x80;

    static final char FWDSLSH = '/';
    static final char FILESEP = 
                    System.getProperty("file.separator").charAt(0);
    static final char JAVADOT = '.';
    static final char LOWLINE = '_';

    public void Assert(boolean p) {
        if (!p)
            throw new IllegalArgumentException( "Assertion Failed"); 
    }
    
    public static String Tag(int tag) {
        switch (tag) {
            case ONLIST: return "ONLIST,";
            case ONTODO: return "ONTODO,";
            case ONSYMS: return "ONSYMS,";
            case FROMJAR: return "FROMJAR,";
            case FROMCLS: return "FROMCLS,";
            case APINEEDS: return "APINEEDS,";
            case FOUNDCPS: return "FOUNDCPS,";
            case CURRENT: return "CURRENT,";
            default: return "unknown,";    
        }
    }
}
