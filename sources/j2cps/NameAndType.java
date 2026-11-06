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
/*               NameAndType Reference class for j2cps                */
/*                                                                    */   
/*  (c) copyright QUT, John Gough 2000-2012, John Gough, 2012-2017    */ 
/**********************************************************************/
package j2cps;

public class NameAndType {

  ConstantPool cp;          /* The constant pool containing this N & T */
  int nameIndex;            /* CP index for this N & T's name          */
  int typeIndex;            /* CP index for this N & T'x type          */
  String name;
  String type;

  public NameAndType(ConstantPool thisCp, int nameIx, int typeIx) {
    this.cp = thisCp;
    this.nameIndex = nameIx;
    this.typeIndex = typeIx;
  }

  public String GetName() {
    if (this.name == null) { this.name = (String) this.cp.Get(nameIndex); }
    return this.name;
  }

  public String GetType() {
    if (this.type == null) { this.type = (String) this.cp.Get(typeIndex); }
    return this.type;
  }

  public void Resolve() {
    if (this.name == null) { this.name = (String) this.cp.Get(nameIndex); }
    if (this.type == null) { this.type = (String) this.cp.Get(typeIndex); }
  }

    @Override
  public String toString() {
    this.Resolve();
    return "<NameAndType> " + nameIndex + " " + this.name + 
           "              " + typeIndex + " " + this.type;
  }

}
