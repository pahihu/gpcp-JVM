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
/*                Pointer Descriptor class for j2cps                  */
/*                                                                    */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017    */ 
/**********************************************************************/
package j2cps;

import java.io.DataOutputStream;
import java.io.IOException;

public class PtrDesc extends TypeDesc {

  TypeDesc boundType;

  public PtrDesc(TypeDesc baseType) {
    this.typeOrd = TypeDesc.arrPtr;
    this.boundType = baseType;
    if (this.boundType != null) { 
        this.name = "POINTER TO " + this.boundType.name; 
    }
  }

  public PtrDesc(int inNum, int baseNum) {
    this.typeOrd = TypeDesc.arrPtr;
    this.inTypeNum = inNum;
    this.inBaseTypeNum = baseNum;
  }
  
  public void Init(TypeDesc baseType) {
    this.boundType = baseType;
    if (this.boundType != null) { setName(); }
  }

  public void AddImportToPtr(ClassDesc thisClass) {
    if (this.boundType instanceof ClassDesc) {
        ((ClassDesc)this.boundType).blame = this.blame;
        thisClass.AddImportToClass((ClassDesc)this.boundType);
    } else if (this.boundType instanceof ArrayDesc) {
        ((ArrayDesc)this.boundType).blame = this.blame;
        ((ArrayDesc)this.boundType).AddImportToArray(thisClass);
    }
  }

  public void setName() {
    this.name = "POINTER TO " + this.boundType.name;
  }
  
  /** Write a pointer type definition to the typelist section of a symbol file.
   * <p>
   * A pointer type declaration consists of only an array marker
   * followed by the type-ordinal of the bound type.
   * 
   * @param out  the symbol file output stream
   * @param thisPack the package which this symbol file describes
   * @throws IOException 
   */
  

    @Override
  public void writeType(DataOutputStream out, PackageDesc thisPack) 
                                                           throws IOException {
    out.writeByte(SymbolFile.ptrSy);
    SymbolFile.writeTypeOrd(out,this.boundType); 
  }


}


