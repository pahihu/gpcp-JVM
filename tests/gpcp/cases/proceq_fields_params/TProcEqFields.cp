(* fixProcEqual: procedure values stored in record fields, arrays and
   passed through parameters must compare structurally, not by wrapper
   object identity. *)
MODULE TProcEqFields;
  IMPORT CPmain, Console;

  TYPE
    Hook = PROCEDURE (x: INTEGER): INTEGER;
    Holder = RECORD cb: Hook END;

  VAR
    h: Holder;
    f: Hook;
    arr: ARRAY 2 OF Hook;

  PROCEDURE Double(x: INTEGER): INTEGER;
  BEGIN RETURN 2*x END Double;

  PROCEDURE Same(a: Hook; b: Hook): BOOLEAN;
  BEGIN RETURN a = b END Same;

  PROCEDURE Store(VAR dst: Hook; src: Hook);
  BEGIN dst := src END Store;

  PROCEDURE Check(cond: BOOLEAN; IN name: ARRAY OF CHAR);
  BEGIN
    IF cond THEN Console.WriteString("ok   ")
    ELSE Console.WriteString("FAIL ") END;
    Console.WriteString(name);
    Console.WriteLn
  END Check;

BEGIN
  h.cb := Double;
  f := Double;

  Check(h.cb = f,                 "field-vs-var");
  Check(f = h.cb,                 "var-vs-field");
  Check(Same(h.cb, Double),       "param-vs-literal");
  Check(Same(Double, Double),     "two-literal-params");

  Store(f, h.cb);
  Check(f = Double,               "stored-via-varparam");
  Check(f = h.cb,                 "stored-vs-field");

  arr[0] := Double;
  arr[1] := Double;
  Check(arr[0] = arr[1],          "array-elements");
  Check(arr[0] = Double,          "array-vs-literal");

  f := NIL;
  Check(Same(f, NIL),             "nil-param-left");
  Check(Same(NIL, f),             "nil-param-right");
  Check(~Same(f, h.cb),           "nil-vs-field");

  f := Double;
  Check(Same(f, h.cb),            "param-field-var");
  Check(~Same(f, NIL),            "param-vs-nil")
END TProcEqFields.
