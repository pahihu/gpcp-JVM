MODULE MkOver;
  IMPORT CPmain, GPText, GPTextFiles;

  VAR name : ARRAY 8 OF CHAR;
      indx : INTEGER;
      file : GPTextFiles.FILE;

BEGIN
  name := "	c";
  file := GPTextFiles.createFile("TooBig.cp");
  GPText.WriteString(file, "MODULE TooBig;"); GPText.WriteLn(file);
  GPText.WriteString(file, "  CONST"); GPText.WriteLn(file);
  FOR indx := 0 TO 5000 DO
    GPText.WriteString(file, name);
    GPText.WriteInt(file, indx, 1);
    GPText.WriteString(file, "*	 =");
    GPText.WriteInt(file, indx, 6);
    GPText.Write(file, ";");
    GPText.WriteLn(file);
  END;
  GPText.WriteString(file, "END TooBig."); GPText.WriteLn(file);
  GPTextFiles.CloseFile(file);
END MkOver.

