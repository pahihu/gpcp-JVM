MODULE Form;
(* ========================================================================= *
 * This file       : FormHello.cp                                            *
 *                                                                           *
 * Author : SiuYuen Chan                                                     *
 * Date   : July 2001                                                        *
 *                                                                           *
 * The source code is intended only as a sample for demonstrating using      *
 * Component Pascal to program Microsoft .NET applications.                  *
 *                                                                           *
 * THIS CODE IS PROVIDED "AS IS" WITHOUT SUPPORT OR GUARANTEE OF ANY KIND.   *
 * ========================================================================= *)

  IMPORT  
        STA, (* Sets the Single Thread Apartment property TRUE *)
        Sys := "[mscorlib]System",  (* This format needs GPCP 1.3.6 or later *)
        Cpm := "[system]System.ComponentModel",
        Wfm := "[system.windows.forms]System.Windows.Forms",
        Drw := "[system.drawing]System.Drawing",
        WinMain;

  TYPE  ButtonForm* = POINTER TO
            RECORD (Wfm.Form)
              button1    : Wfm.Button;
              button2    : Wfm.Button;
              components : Cpm.Container;
            END;

  VAR   bf: ButtonForm;

  PROCEDURE (bf: ButtonForm) Dispose*(disposing: BOOLEAN);
  BEGIN
    IF disposing THEN
        IF bf.components # NIL THEN
            bf.components.Dispose();
        END; (* IF *)
        bf.Dispose^(disposing);
    END; (* IF *)
  END Dispose;

  PROCEDURE (bf: ButtonForm) button1_Click*(sender: Sys.Object;
                                           e: Sys.EventArgs), NEW;
    VAR rslt: Wfm.DialogResult;
  BEGIN
    rslt := Wfm.MessageBox.Show("Hello! button is pressed!", 
                                "Hello Button World");
  END button1_Click;

  PROCEDURE (bf: ButtonForm) button2_Click*(sender: Sys.Object;
                                           e: Sys.EventArgs), NEW;
    VAR rslt: Wfm.DialogResult;
  BEGIN
    rslt := Wfm.MessageBox.Show("Really goodbye?", 
                                "Hello Button World", 
                                Wfm.MessageBoxButtons.YesNo);
    IF rslt = Wfm.DialogResult.Yes THEN bf.Dispose(TRUE) END;
  END button2_Click;

  PROCEDURE (bf: ButtonForm) InitializeComponent(), NEW;
  BEGIN
    NEW(bf.components);
    NEW(bf.button1);
    NEW(bf.button2);
    bf.SuspendLayout();

    bf.button1.set_Location(Drw.Point.init(72, 96));
    bf.button1.set_Size(Drw.Size.init(160, 32));
    bf.button1.set_TabIndex(0);
    bf.button1.set_Text("Hello");

    bf.button2.set_Location(Drw.Point.init(72, 136));
    bf.button2.set_Size(Drw.Size.init(160, 32));
    bf.button2.set_TabIndex(1);
    bf.button2.set_Text("Goodbye");

    REGISTER(bf.button1.Click, bf.button1_Click);
    REGISTER(bf.button2.Click, bf.button2_Click);
    bf.set_Text("Button Sample");
    bf.set_AutoScaleBaseSize(Drw.Size.init(5, 13));
    bf.get_Controls().Add(bf.button1);
    bf.get_Controls().Add(bf.button2);
  END InitializeComponent;

BEGIN
    NEW(bf);
(*
 *  NEW(ct);
 *  cc := Wfm.Control$ControlCollection.init(ct);
 *)
    bf.InitializeComponent();
    Wfm.Application.Run(bf);
END Form.
