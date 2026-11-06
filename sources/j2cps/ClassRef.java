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

/*************************************************************************/
/*                Class Reference class for j2cps                        */
/* Represents the class references in the constant pool of a class file  */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017       */ 
/*************************************************************************/
package j2cps;

public class ClassRef {

  ConstantPool cp;  /* the constant pool containing this class ref */
  String name;      /* the name of this class */
  int nameIndex;    /* the index into the constant pool */
                    /* for the name of this class       */
  ClassDesc info;   /* this class info for this class ref */
  
  public ClassRef(ConstantPool thisCp, int nameIndex) {
    this.cp = thisCp;
    this.nameIndex = nameIndex;
  }
 
  public String GetName() {
    if (name == null) { name = (String) cp.Get(nameIndex); }
    return name;
  }
  
  public ClassDesc GetClassDesc() {
    if (info == null) {
      if (name == null) { name = (String) this.cp.Get(nameIndex); }
      info = ClassDesc.GetClassDesc(name,null);
    }
    return info;
  }

  public boolean equals(ClassRef anotherClass) {
    return this.GetName().equals(anotherClass.GetName());
  }
  
  public void Resolve() {
    if (name == null) { this.name = (String) this.cp.Get(nameIndex); }
  }

    @Override
  public String toString() {
    this.Resolve();
    return ("<ClassReference> " + nameIndex + " " + name);
  }
}










