(*
 *  Testing the STA pseudo-module
 *  Only works on GPCP-CLR.
 *  Should give an error if compiled by GPCP-JVM
 *)

MODULE STAtest2;

 (* gpcp -hsize=30000 STAtest.cp *)

 IMPORT
   STA,
   Sys := "[mscorlib]System",
   SysThr := "[mscorlib]System.Threading",
   CPmain, Console;

 BEGIN
    Console.WriteString("Hello CP World!"); Console.WriteLn;
    (* Show proof that we are running [STAThread]... *)
    Console.WriteString("I am running as STAThread: ");

    Sys.Console.WriteLine(SysThr.Thread.get_CurrentThread().get_ApartmentState() 
                = SysThr.ApartmentState.STA);

 END STAtest2.

