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
/*                    FieldInfo class for j2cps                       */
/*                                                                    */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017    */ 
/**********************************************************************/
package j2cps;

import java.io.DataInputStream;
import java.io.IOException;


public class FieldInfo extends MemberInfo {
  
    Object constVal;
    public TypeDesc type;
    public int typeFixUp = 0;

    public FieldInfo(ConstantPool cp, DataInputStream stream,
                   ClassDesc thisClass) throws IOException {    
        super(cp,stream,thisClass);
        this.type = TypeDesc.GetType(this.signature,0);
    }

    public FieldInfo(ClassDesc cl,int acc,String nam,TypeDesc typ,Object cVal) {
        super(cl,acc,nam);
        this.type = typ;
        this.constVal = cVal;
    }

//  @Override
//  public void AddImport(ClassDesc thisClass) {
//    if (type instanceof ClassDesc) { thisClass.AddImport((ClassDesc)type); }
//  }

    public void GetConstValueAttribute (ConstantPool cp, DataInputStream stream) 
                                                              throws IOException {
        int attLen = stream.readInt();
        constVal = cp.Get(stream.readUnsignedShort()); 
        if (constVal instanceof StringRef) {
            constVal = ((StringRef)constVal).GetString();
        }
    }

    public Object GetConstVal() {
        return constVal;
    }

    public boolean isConstant() {
        return ((constVal != null) && ConstantPool.isFinal(accessFlags) &&
                ConstantPool.isStatic(accessFlags) && 
                (ConstantPool.isPublic(accessFlags) || 
                ConstantPool.isProtected(accessFlags)));
    }

  @Override
  public String toString() {
    if (constVal == null) {
      return ConstantPool.GetAccessString(accessFlags) + " " + 
             signature + " " + name;
    } else {
      return ConstantPool.GetAccessString(accessFlags) + " " + 
             signature + " " + name + " = " + constVal.toString();
    }
  }

}
