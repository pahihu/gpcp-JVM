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
/*                  Member Info class for j2cps                       */
/*                                                                    */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017    */ 
/**********************************************************************/
package j2cps;

import java.io.DataInputStream;
import java.io.IOException;

public class MemberInfo {

  public ClassDesc owner;
  public int accessFlags;
  public String name;
  public String signature;
  
  public MemberInfo(ConstantPool cp,DataInputStream stream,ClassDesc own) 
                                                            throws IOException {
    owner = own;
    accessFlags = stream.readUnsignedShort();
    name = (String) cp.Get(stream.readUnsignedShort());
    signature = (String) cp.Get(stream.readUnsignedShort());
    /* skip the attributes */
    int attrCount = stream.readUnsignedShort();
    for (int i = 0; i < attrCount; i++) {  
      int attNameIx = stream.readUnsignedShort();
      if ("ConstantValue".equals((String)cp.Get(attNameIx)) &&
         (this instanceof FieldInfo)) {
        ((FieldInfo)this).GetConstValueAttribute(cp,stream);
      } else {
        if ("Deprecated".equals((String)cp.Get(attNameIx)) &&
         (this instanceof MethodInfo)) { ((MethodInfo)this).deprecated = true; }
        int attrLength = stream.readInt();
        for (int j = 0; j < attrLength; j++) {
          int tmp = stream.readByte();
        }
      }
    }
  }

  public MemberInfo(ClassDesc own,int acc,String nam) {
    owner = own;
    accessFlags = acc;
    name = nam;
  }

  public boolean isPublicStatic() {
    return ConstantPool.isStatic(accessFlags) && 
           ConstantPool.isPublic(accessFlags);
  }

  public final boolean isExported() {
    return (ConstantPool.isPublic(accessFlags) ||
            ConstantPool.isProtected(accessFlags)); 
  }

  public boolean isPublic() {
    return ConstantPool.isPublic(accessFlags); 
  }

  public boolean isStatic() {
    return ConstantPool.isStatic(accessFlags); 
  }

  public boolean isPrivate() {
    return ConstantPool.isPrivate(accessFlags); 
  }

  public boolean isProtected() {
    return ConstantPool.isProtected(accessFlags); 
  }

  public boolean isAbstract() {
    return ConstantPool.isAbstract(accessFlags); 
  }

  public boolean isFinal() {
    return ConstantPool.isFinal(accessFlags); 
  }

    @Override
  public String toString() { return ""; };

  
}
