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

/**********************************************************************/
/*                  Method Info class for j2cps                       */
/*                                                                    */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017    */ 
/**********************************************************************/
package j2cps;

import java.io.DataInputStream;
import java.io.IOException;

public class MethodInfo extends MemberInfo {

    public TypeDesc[] parTypes;
    public TypeDesc retType;
    public String userName;
    public boolean deprecated = false;
    public int retTypeFixUp = 0;
    public int[] parFixUps;
    public boolean overridding = false;
    public boolean isInitProc = false;
    public boolean isCLInitProc = false;

    public MethodInfo(ConstantPool cp,DataInputStream stream,
                      ClassDesc thisClass) throws IOException {
        super(cp,stream,thisClass);
        this.parTypes = TypeDesc.GetParTypes(signature);
        this.retType = TypeDesc.GetType(signature,signature.indexOf(')')+1);
        if (this.name.equals("<init>")) { 
            this.userName = "Init"; 
            this.isInitProc = true;
            if (!ConstantPool.isStatic(accessFlags)) {
              this.accessFlags = (this.accessFlags + ConstantPool.ACC_STATIC);
            }
            if ((this.parTypes.length == 0) && 
                    (!ConstantPool.isPrivate(this.accessFlags))) { 
              thisClass.hasNoArgConstructor = true; 
            }
            this.retType = thisClass;
        } else if (this.name.equals("<clinit>")) {
            this.userName="CLInit"; 
            this.isCLInitProc = true;
        } else {
            this.userName=this.name;
        }
        if (ClassDesc.VERBOSE) {
            int parNm = this.parTypes.length;
            System.out.printf("Method %s has %d %s",
                    this.name, parNm, (parNm != 1 ?
                        "parameters" : "parameter"));
        }
        if (this.isExported()) {
            for (TypeDesc parType : this.parTypes) {
                // 
                //  The package of this type must be placed on 
                //  this package's import list iff:
                //   *  the par type is public or protected AND
                //   *  the method's package is not CURRENT.
                //
                if (parType.parentPkg != thisClass.parentPkg) {
                    parType.blame = this;
                    thisClass.TryImport(parType);
                }
            }
            if (this.retType.parentPkg != thisClass.parentPkg) {
                this.retType.blame = this;
                thisClass.TryImport(this.retType);
            }
        }
    }

  public MethodInfo(ClassDesc thisClass,String name,String jName,int acc) {
    super(thisClass,acc,jName);
    this.userName = name;
    if (name.equals("<init>")) { 
      if (userName == null) { 
          this.userName = "Init";
      }
      this.isInitProc = true; 
    }
  }

    @Override
  public String toString() {
    return ConstantPool.GetAccessString(this.accessFlags) + " " + 
            this.name + " " + this.signature;
  }

}
