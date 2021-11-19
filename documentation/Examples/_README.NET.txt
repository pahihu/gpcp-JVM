---------------------------------------------
Gardens Point Component Pascal Compiler. (.NET)
---------------------------------------------
Instructions for compiling the various demo programs.
0. General Instructions:
----------------------------
a) The compiler must be on your PATH, probably %CROOT%\bin
b) The compiler must be able to find the library symbol files, probably by
	using the environment variable CPSYM. 
c) In order for programs to run you will need to have access to any DLLs that
	are referenced.  These are NOT found from the PATH, unless the
	executable has been found on the path.  You should copy RTS.dll
	into this working directory, if it not already there.
	copy %CROOT%\bin\RTS.dll .
        You can load RTS and GP*Files libraries using the batch file
        CopyNetLibs.bat in the %CROOT%\bin directory.
        > CopyNetLibs.bat <destination-directory>, or from this directory
        > CopyNetLibs.bat .

0. Hello.
---------------
a) compile with
	gpcp Hello.cp, or even gpcp /verbose Hello.cp
b) execute with
	Hello

1. HelloWorld.
---------------
a) compile with
	gpcp HelloWorld.cp, or even gpcp /verbose HelloWorld.cp
b) execute with
	HelloWorld
c) now try
	HelloWorld more command line args

2. NQueens.
------------
a) compile with
	gpcp NQueens.cp
b) execute with
	NQueens
c) now you know how many solutions there are to the NQueens problem for the
	various board sizes!

3. Hennessy.
--------------
a) compile with
	gpcp Hennessy.cp
b) execute with
	Hennessy
c) These are the Hennessy integer benchmarks.  These might improve slightly
	for later versions, but they are pretty close to native speeds already.

4. MkOver.
--------------
This program tests the hash table overflow detection. You will need to have 
RTS.dll, GPFiles.dll, GPTextFiles.dll copied into this directory
from the gpcp\bin directory. MkOver uses GPText.cp so compile with CPMake

a) compile with
	CPMake MkOver.cp
   this creates the executable MkOver.exe, and compiles GPText.dll. 
b) run MkOver with
	MkOver
   When you run MkOver.exe it will create a file TooBig.cp which has 5000 
   separate constants defined.  
c) try to compile TooBig.cp
	gpcp /hsize=4000 TooBig.cp
   This should trap with a hash table overflow. 
d) Retry compiling with
	gpcp /hSize=6000 TooBig.cp
   All is now ok!

Note that the current default hSize is 8209, so that the compiler will not
trap with the default sizes.

You may browse the code of MkOver.cp to get a simple example of creating
and writing to text files.

5. HelloUplevel.
--------------
a) compile with 
	gpcp HelloUplevel.cp
b) run with 
	HelloUplevel
c) this demonstrates the warnings for programs that perform uplevel addressing.


5. STAtest2.  [NET ONLY]
--------------
a) compile with 
	gpcp STAtest2.cp
b) run with 
        STAtest2
c) this demonstrates the new STA library in V1.3.12

6. ToStringDemo.cp
--------------
a) compile with
	gpcp ToStringDemo.cp
b) run with 
	ToStringDemo
c) This demonstrates how to override the .NET Object virtual method ToString
   which is used as the default transformation for string format methods etc.

7. TypeNames.cp
--------------
a) compile with
	gpcp TypeNames.cp
b) run with 
	TypeNames
c) this demonstrates the RTS facilities for getting the target-specific
   names of the implementation types that gpcp uses for various CP types.

8. TestBangString
--------------
a) compile with 
	gpcp ExportBangString.cp TestBangString.cp 
b) you can also compile with
	CPMake TestBangString
c) run with 
	TestBangString
d) this demonstrates the new "bang-string" extension in V1.3.12


9. MkstrAndBox
--------------
Some examples of the MKSTR and BOX functions.

10. Vectors
--------------
Some examples clarifying the semantics of assignment for the VECTOR types.

11 Form [NET ONLY]
--------------
Hello World for Windows Forms.
a) compile with
        gpcp /hsize=16000 Form.cp
   Programs importing Systems.Windows.Forms use up > 12000 symtab entries.
b) run with 
        Form
c) click the buttons!

12. TestAdr [NET ONLY]
--------------
a) compile with 
        gpcp /unsafe TestAdr.cp
b) run with 
        TestAdr
c) Notice that, for example, ADR(arr) # ADR(arr[0])
   In fact ADR(arr[0]) = ADR(arr) + 16 for my runtime.

13. NetParams [NET ONLY]
--------------
a) compile with 
        gpcp NetParams.cp
b) run with 
        NetParams <up to eight args>
c) This example shows how to call varargs methods.

14. JvmParams [JVM ONLY]
--------------
a) JVM version of NetParams.cp

--------------------------- Have Fun ------------------------------------------

