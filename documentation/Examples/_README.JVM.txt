---------------------------------------------
Gardens Point Component Pascal Compiler. (JVM)
---------------------------------------------
Instructions for compiling the various demo programs.
0. General Instructions:
----------------------------
a) The compiler launch scripts must be on your PATH, probably %JROOT%\bin
b) The compiler must be able to find the library symbol files, probably by
	using the environment variable CPSYM. 

0. Hello.
---------------
a) compile with
	gpcp Hello.cp, or even gpcp -verbose Hello.cp
b) execute with
	cprun Hello

1. HelloWorld.
---------------
a) compile with
	gpcp HelloWorld.cp, or even gpcp -verbose HelloWorld.cp
b) execute with
	cprun HelloWorld
c) now try
	cprun HelloWorld more command line args

2. NQueens.
------------
a) compile with
	gpcp NQueens.cp
b) execute with
	cprun NQueens
c) now you know how many solutions there are to the NQueens problem for the
	various board sizes!

3. Hennessy.
--------------
a) compile with
	gpcp Hennessy.cp
b) execute with
	cprun Hennessy
c) These are the Hennessy integer benchmarks.  These might improve slightly
	for later versions, but they are pretty close to native speeds already.

4. MkOver.
--------------
This program tests the hash table overflow detection. You will need to have 
RTS.dll, GPFiles.dll, GPTextFiles.dll copied into this directory
from the gpcp\bin directory. MkOver uses GPText.cp so compile with CPMake

a) compile with
	CPMake MkOver.cp
   this creates the executable MkOver.exe, and also compiles GPText.dll. 
b) run MkOver with
	cprun MkOver
   When you run MkOver.exe it will create a file TooBig.cp which has 
   > 5000 separate constants defined.  
c) try to compile TooBig.cp
	gpcp -hsize:4000 TooBig.cp
   This should trap with a hash table overflow. 
d) Retry compiling with
	gpcp -hSize:6000 TooBig.cp
   All is now ok!

Note that the current default hSize is 8209, so that the compiler will not
trap with the default sizes.

You may browse the code of MkOver.cp to see a simple example of creating
and writing to text files.

5. HelloUplevel.
--------------
a) compile with 
	gpcp HelloUplevel.cp
b) run with 
	cprun HelloUplevel
c) this demonstrates the warnings for programs that perform uplevel addressing.

5. STAtest2.  [NET ONLY]
--------------

6. ToStringDemo.cp [NET ONLY]
--------------
a) compile with
	gpcp ToStringDemo.cp
b) run with 
	cprun ToStringDemo
c) This demonstrates how to override the .NET Object virtual method ToString
   which is used as the default transformation for string format methods etc.

7. TypeNames.cp
--------------
a) compile with
	gpcp TypeNames.cp
b) run with 
	cprun TypeNames
c) this demonstrates the RTS facilities for getting the target-specific
   names of the implementation types that gpcp uses for various CP types.

8. TestBangString
--------------
a) compile with 
	gpcp ExportBangString.cp TestBangString.cp 
b) you can also compile with
	CPMake TestBangString
c) run with 
	cprun TestBangString
d) this demonstrates the new "bang-string" extension in V1.3.12

9. MkstrAndBox
--------------
Some examples of the MKSTR and BOX functions.

10. Vectors
--------------
Some examples clarifying the semantics of assignment for the VECTOR types.

11. Form [NET ONLY]
--------------

11. TestAdr [NET ONLY]
--------------

13. NetParams [NET ONLY]
--------------
   NET version of JvmParams.cp

14. JvmParams [JVM ONLY]
--------------
a) compile with 
        gpcp -nowarn JvmParams.cp
   without the option you will get several warnings about possibly 
   ambiguous bindings of "println(int)", because of the automatic coercions
   that java does in such cases (LONGINT, SHORTREAL, REAL and even java_lang.Object). 
   Gpcp will bind to the version that takes the INTEGER, since this is the only case 
   that does not need an type conversion of the offered argument.
b) run with 
        cprun NetParams <up to eight args>
c) This example shows how to call varargs methods.


--------------------------- Have Fun ------------------------------------------

