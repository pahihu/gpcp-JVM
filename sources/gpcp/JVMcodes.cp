(* ============================================================ *)
(*  JVMcodes is the module which defines jasmin name ordinals.  *)
(*  Name spelling is defined by the lexical rules of Jasmin.	*)
(*  Copyright (c) John Gough 1999, 2000.			*)
(* ============================================================ *)

MODULE JVMcodes;
  IMPORT GPCPcopyright;

(* ============================================================ *)

  CONST
        dot_error*     = 0;
        dot_catch*     = 1;
        dot_class*     = 2;
        dot_end*       = 3;
        dot_field*     = 4;
        dot_implements*= 5;
        dot_interface* = 6;
        dot_limit*     = 7;
        dot_line*      = 8;
        dot_method*    = 9;
        dot_source*    = 10;
        dot_super*     = 11;
        dot_throws*    = 12;
        dot_var*       = 13;

  CONST
        att_empty*       = {};
        att_public*      = {0};
        att_private*     = {1};
        att_protected*   = {2};
        att_static*      = {3};
        att_final*       = {4};
        att_synchronized*= {5};
        att_native*      = {6};
        att_volatile*    = {7};
        att_abstract*    = {8};
        att_transient*   = {9};
        att_interface*   = {10};

(* Constants for java class files *)

  CONST
        (* access flags *)
        acc_package*      = 0000H;
        acc_public*       = 0001H;
        acc_private*      = 0002H;
        acc_protected*    = 0004H;
        acc_static*       = 0008H;
        acc_final*        = 0010H;
        acc_synchronized* = 0020H;
        acc_volatile*     = 0040H;
        acc_transient*    = 0080H;
        acc_super*        = 0020H;
        acc_native*       = 0100H;
        acc_interface*    = 0200H;
        acc_abstract*     = 0400H;

        (* constant pool tags *)
        const_utf8*               =  1;
        const_integer*            =  3;
        const_float*              =  4;
        const_long*               =  5;
        const_double*             =  6;
        const_class*              =  7;
        const_string*             =  8;
        const_fieldref*           =  9;
        const_methodref*          = 10;
        const_interfacemethodref* = 11;
        const_nameandtype*        = 12;

(* ============================================================ *)

  CONST
	opc_nop*	= 0;
	opc_aconst_null*= 1;
	opc_iconst_m1*	= 2;
	opc_iconst_0*	= 3;
	opc_iconst_1*	= 4;
	opc_iconst_2*	= 5;
	opc_iconst_3*	= 6;
	opc_iconst_4*	= 7;
	opc_iconst_5*	= 8;
	opc_lconst_0*	= 9;
	opc_lconst_1*	= 10;
	opc_fconst_0*	= 11;
	opc_fconst_1*	= 12;
	opc_fconst_2*	= 13;
	opc_dconst_0*	= 14;
	opc_dconst_1*	= 15;
	opc_bipush*	= 16;
	opc_sipush*	= 17;
	opc_ldc*	= 18;
	opc_ldc_w*	= 19;
	opc_ldc2_w*	= 20;
	opc_iload*	= 21;
	opc_lload*	= 22;
	opc_fload*	= 23;
	opc_dload*	= 24;
	opc_aload*	= 25;
	opc_iload_0*	= 26;
	opc_iload_1*	= 27;
	opc_iload_2*	= 28;
	opc_iload_3*	= 29;
	opc_lload_0*	= 30;
	opc_lload_1*	= 31;
	opc_lload_2*	= 32;
	opc_lload_3*	= 33;
	opc_fload_0*	= 34;
	opc_fload_1*	= 35;
	opc_fload_2*	= 36;
	opc_fload_3*	= 37;
	opc_dload_0*	= 38;
	opc_dload_1*	= 39;
	opc_dload_2*	= 40;
	opc_dload_3*	= 41;
	opc_aload_0*	= 42;
	opc_aload_1*	= 43;
	opc_aload_2*	= 44;
	opc_aload_3*	= 45;
	opc_iaload*	= 46;
	opc_laload*	= 47;
	opc_faload*	= 48;
	opc_daload*	= 49;
	opc_aaload*	= 50;
	opc_baload*	= 51;
	opc_caload*	= 52;
	opc_saload*	= 53;
	opc_istore*	= 54;
	opc_lstore*	= 55;
	opc_fstore*	= 56;
	opc_dstore*	= 57;
	opc_astore*	= 58;
	opc_istore_0*	= 59;
	opc_istore_1*	= 60;
	opc_istore_2*	= 61;
	opc_istore_3*	= 62;
	opc_lstore_0*	= 63;
	opc_lstore_1*	= 64;
	opc_lstore_2*	= 65;
	opc_lstore_3*	= 66;
	opc_fstore_0*	= 67;
	opc_fstore_1*	= 68;
	opc_fstore_2*	= 69;
	opc_fstore_3*	= 70;
	opc_dstore_0*	= 71;
	opc_dstore_1*	= 72;
	opc_dstore_2*	= 73;
	opc_dstore_3*	= 74;
	opc_astore_0*	= 75;
	opc_astore_1*	= 76;
	opc_astore_2*	= 77;
	opc_astore_3*	= 78;
	opc_iastore*	= 79;
	opc_lastore*	= 80;
	opc_fastore*	= 81;
	opc_dastore*	= 82;
	opc_aastore*	= 83;
	opc_bastore*	= 84;
	opc_castore*	= 85;
	opc_sastore*	= 86;
	opc_pop*	= 87;
	opc_pop2*	= 88;
	opc_dup*	= 89;
	opc_dup_x1*	= 90;
	opc_dup_x2*	= 91;
	opc_dup2*	= 92;
	opc_dup2_x1*	= 93;
	opc_dup2_x2*	= 94;
	opc_swap*	= 95;
	opc_iadd*	= 96;
	opc_ladd*	= 97;
	opc_fadd*	= 98;
	opc_dadd*	= 99;
	opc_isub*	= 100;
	opc_lsub*	= 101;
	opc_fsub*	= 102;
	opc_dsub*	= 103;
	opc_imul*	= 104;
	opc_lmul*	= 105;
	opc_fmul*	= 106;
	opc_dmul*	= 107;
	opc_idiv*	= 108;
	opc_ldiv*	= 109;
	opc_fdiv*	= 110;
	opc_ddiv*	= 111;
	opc_irem*	= 112;
	opc_lrem*	= 113;
	opc_frem*	= 114;
	opc_drem*	= 115;
	opc_ineg*	= 116;
	opc_lneg*	= 117;
	opc_fneg*	= 118;
	opc_dneg*	= 119;
	opc_ishl*	= 120;
	opc_lshl*	= 121;
	opc_ishr*	= 122;
	opc_lshr*	= 123;
	opc_iushr*	= 124;
	opc_lushr*	= 125;
	opc_iand*	= 126;
	opc_land*	= 127;
	opc_ior*	= 128;
	opc_lor*	= 129;
	opc_ixor*	= 130;
	opc_lxor*	= 131;
	opc_iinc*	= 132;
	opc_i2l*	= 133;
	opc_i2f*	= 134;
	opc_i2d*	= 135;
	opc_l2i*	= 136;
	opc_l2f*	= 137;
	opc_l2d*	= 138;
	opc_f2i*	= 139;
	opc_f2l*	= 140;
	opc_f2d*	= 141;
	opc_d2i*	= 142;
	opc_d2l*	= 143;
	opc_d2f*	= 144;
	opc_i2b*	= 145;
	opc_i2c*	= 146;
	opc_i2s*	= 147;
	opc_lcmp*	= 148;
	opc_fcmpl*	= 149;
	opc_fcmpg*	= 150;
	opc_dcmpl*	= 151;
	opc_dcmpg*	= 152;
	opc_ifeq*	= 153;
	opc_ifne*	= 154;
	opc_iflt*	= 155;
	opc_ifge*	= 156;
	opc_ifgt*	= 157;
	opc_ifle*	= 158;
	opc_if_icmpeq*	= 159;
	opc_if_icmpne*	= 160;
	opc_if_icmplt*	= 161;
	opc_if_icmpge*	= 162;
	opc_if_icmpgt*	= 163;
	opc_if_icmple*	= 164;
	opc_if_acmpeq*	= 165;
	opc_if_acmpne*	= 166;
	opc_goto*	= 167;
	opc_jsr*	= 168;
	opc_ret*	= 169;
	opc_tableswitch*	= 170;
	opc_lookupswitch*	= 171;
	opc_ireturn*		= 172;
	opc_lreturn*		= 173;
	opc_freturn*		= 174;
	opc_dreturn*		= 175;
	opc_areturn*		= 176;
	opc_return*		= 177;
	opc_getstatic*		= 178;
	opc_putstatic*		= 179;
	opc_getfield*		= 180;
	opc_putfield*		= 181;
	opc_invokevirtual*	= 182;
	opc_invokespecial*	= 183;
	opc_invokestatic*	= 184;
	opc_invokeinterface*	= 185;
	opc_xxxunusedxxx	= 186;
	opc_new*		= 187;
	opc_newarray*		= 188;
	opc_anewarray*		= 189;
	opc_arraylength*	= 190;
	opc_athrow*		= 191;
	opc_checkcast*		= 192;
	opc_instanceof*		= 193;
	opc_monitorenter*	= 194;
	opc_monitorexit*	= 195;
	opc_wide*		= 196;
	opc_multianewarray*	= 197;
	opc_ifnull*		= 198;
	opc_ifnonnull*		= 199;
	opc_goto_w*		= 200;
	opc_jsr_w*		= 201;
	opc_breakpoint*		= 202;

(* ============================================================ *)

  TYPE
     OpName* = ARRAY 24 OF CHAR;

(* ============================================================ *)

  VAR	op* : ARRAY 203 OF OpName;
	dl* : ARRAY 203 OF INTEGER;

  VAR   dirStr* : ARRAY 14 OF OpName;
	access* : ARRAY 12 OF OpName;

(* ============================================================ *)

BEGIN
        dirStr[dot_error]       := ".ERROR";
        dirStr[dot_catch]       := ".catch";
        dirStr[dot_class]       := ".class";
        dirStr[dot_end]         := ".end method";
        dirStr[dot_field]       := ".field";
        dirStr[dot_implements]  := ".implements";
        dirStr[dot_interface]   := ".interface";
        dirStr[dot_limit]       := ".limit";
        dirStr[dot_line]        := ".line";
        dirStr[dot_method]      := ".method";
        dirStr[dot_source]      := ".source";
        dirStr[dot_super]       := ".super";
        dirStr[dot_throws]      := ".throws";
        dirStr[dot_var]         := ".var";

	access[ 0]		:= "public";
	access[ 1]		:= "private";
	access[ 2]		:= "protected";
	access[ 3]		:= "static";
	access[ 4]		:= "final";
	access[ 5]		:= "synchronized";
	access[ 6]		:= "native";
	access[ 7]		:= "volatile";
	access[ 8]		:= "abstract";
	access[ 9]		:= "transient";
	access[10]		:= "interface";

	op[opc_nop] 		:= "nop";
	op[opc_aconst_null]	:= "aconst_null";
	op[opc_iconst_m1]	:= "iconst_m1";
	op[opc_iconst_0]	:= "iconst_0";
	op[opc_iconst_1]	:= "iconst_1";
	op[opc_iconst_2]	:= "iconst_2";
	op[opc_iconst_3]	:= "iconst_3";
	op[opc_iconst_4]	:= "iconst_4";
	op[opc_iconst_5]	:= "iconst_5";
	op[opc_lconst_0]	:= "lconst_0";
	op[opc_lconst_1]	:= "lconst_1";
	op[opc_fconst_0]	:= "fconst_0";
	op[opc_fconst_1]	:= "fconst_1";
	op[opc_fconst_2]	:= "fconst_2";
	op[opc_dconst_0]	:= "dconst_0";
	op[opc_dconst_1]	:= "dconst_1";
	op[opc_bipush]		:= "bipush";
	op[opc_sipush]		:= "sipush";
	op[opc_ldc]		:= "ldc";
	op[opc_ldc_w]		:= "ldc_w";
	op[opc_ldc2_w]		:= "ldc2_w";
	op[opc_iload]		:= "iload";
	op[opc_lload]		:= "lload";
	op[opc_fload]		:= "fload";
	op[opc_dload]		:= "dload";
	op[opc_aload]		:= "aload";
	op[opc_iload_0]		:= "iload_0";
	op[opc_iload_1]		:= "iload_1";
	op[opc_iload_2]		:= "iload_2";
	op[opc_iload_3]		:= "iload_3";
	op[opc_lload_0]		:= "lload_0";
	op[opc_lload_1]		:= "lload_1";
	op[opc_lload_2]		:= "lload_2";
	op[opc_lload_3]		:= "lload_3";
	op[opc_fload_0]		:= "fload_0";
	op[opc_fload_1]		:= "fload_1";
	op[opc_fload_2]		:= "fload_2";
	op[opc_fload_3]		:= "fload_3";
	op[opc_dload_0]		:= "dload_0";
	op[opc_dload_1]		:= "dload_1";
	op[opc_dload_2]		:= "dload_2";
	op[opc_dload_3]		:= "dload_3";
	op[opc_aload_0]		:= "aload_0";
	op[opc_aload_1]		:= "aload_1";
	op[opc_aload_2]		:= "aload_2";
	op[opc_aload_3]		:= "aload_3";
	op[opc_iaload]		:= "iaload";
	op[opc_laload]		:= "laload";
	op[opc_faload]		:= "faload";
	op[opc_daload]		:= "daload";
	op[opc_aaload]		:= "aaload";
	op[opc_baload]		:= "baload";
	op[opc_caload]		:= "caload";
	op[opc_saload]		:= "saload";
	op[opc_istore]		:= "istore";
	op[opc_lstore]		:= "lstore";
	op[opc_fstore]		:= "fstore";
	op[opc_dstore]		:= "dstore";
	op[opc_astore]		:= "astore";
	op[opc_istore_0]	:= "istore_0";
	op[opc_istore_1]	:= "istore_1";
	op[opc_istore_2]	:= "istore_2";
	op[opc_istore_3]	:= "istore_3";
	op[opc_lstore_0]	:= "lstore_0";
	op[opc_lstore_1]	:= "lstore_1";
	op[opc_lstore_2]	:= "lstore_2";
	op[opc_lstore_3]	:= "lstore_3";
	op[opc_fstore_0]	:= "fstore_0";
	op[opc_fstore_1]	:= "fstore_1";
	op[opc_fstore_2]	:= "fstore_2";
	op[opc_fstore_3]	:= "fstore_3";
	op[opc_dstore_0]	:= "dstore_0";
	op[opc_dstore_1]	:= "dstore_1";
	op[opc_dstore_2]	:= "dstore_2";
	op[opc_dstore_3]	:= "dstore_3";
	op[opc_astore_0]	:= "astore_0";
	op[opc_astore_1]	:= "astore_1";
	op[opc_astore_2]	:= "astore_2";
	op[opc_astore_3]	:= "astore_3";
	op[opc_iastore]		:= "iastore";
	op[opc_lastore]		:= "lastore";
	op[opc_fastore]		:= "fastore";
	op[opc_dastore]		:= "dastore";
	op[opc_aastore]		:= "aastore";
	op[opc_bastore]		:= "bastore";
	op[opc_castore]		:= "castore";
	op[opc_sastore]		:= "sastore";
	op[opc_pop]		:= "pop";
	op[opc_pop2]		:= "pop2";
	op[opc_dup]		:= "dup";
	op[opc_dup_x1]		:= "dup_x1";
	op[opc_dup_x2]		:= "dup_x2";
	op[opc_dup2]		:= "dup2";
	op[opc_dup2_x1]		:= "dup2_x1";
	op[opc_dup2_x2]		:= "dup2_x2";
	op[opc_swap]		:= "swap";
	op[opc_iadd]		:= "iadd";
	op[opc_ladd]		:= "ladd";
	op[opc_fadd]		:= "fadd";
	op[opc_dadd]		:= "dadd";
	op[opc_isub]		:= "isub";
	op[opc_lsub]		:= "lsub";
	op[opc_fsub]		:= "fsub";
	op[opc_dsub]		:= "dsub";
	op[opc_imul]		:= "imul";
	op[opc_lmul]		:= "lmul";
	op[opc_fmul]		:= "fmul";
	op[opc_dmul]		:= "dmul";
	op[opc_idiv]		:= "idiv";
	op[opc_ldiv]		:= "ldiv";
	op[opc_fdiv]		:= "fdiv";
	op[opc_ddiv]		:= "ddiv";
	op[opc_irem]		:= "irem";
	op[opc_lrem]		:= "lrem";
	op[opc_frem]		:= "frem";
	op[opc_drem]		:= "drem";
	op[opc_ineg]		:= "ineg";
	op[opc_lneg]		:= "lneg";
	op[opc_fneg]		:= "fneg";
	op[opc_dneg]		:= "dneg";
	op[opc_ishl]		:= "ishl";
	op[opc_lshl]		:= "lshl";
	op[opc_ishr]		:= "ishr";
	op[opc_lshr]		:= "lshr";
	op[opc_iushr]		:= "iushr";
	op[opc_lushr]		:= "lushr";
	op[opc_iand]		:= "iand";
	op[opc_land]		:= "land";
	op[opc_ior]		:= "ior";
	op[opc_lor]		:= "lor";
	op[opc_ixor]		:= "ixor";
	op[opc_lxor]		:= "lxor";
	op[opc_iinc]		:= "iinc";
	op[opc_i2l]		:= "i2l";
	op[opc_i2f]		:= "i2f";
	op[opc_i2d]		:= "i2d";
	op[opc_l2i]		:= "l2i";
	op[opc_l2f]		:= "l2f";
	op[opc_l2d]		:= "l2d";
	op[opc_f2i]		:= "f2i";
	op[opc_f2l]		:= "f2l";
	op[opc_f2d]		:= "f2d";
	op[opc_d2i]		:= "d2i";
	op[opc_d2l]		:= "d2l";
	op[opc_d2f]		:= "d2f";
	op[opc_i2b]		:= "i2b";
	op[opc_i2c]		:= "i2c";
	op[opc_i2s]		:= "i2s";
	op[opc_lcmp]		:= "lcmp";
	op[opc_fcmpl]		:= "fcmpl";
	op[opc_fcmpg]		:= "fcmpg";
	op[opc_dcmpl]		:= "dcmpl";
	op[opc_dcmpg]		:= "dcmpg";
	op[opc_ifeq]		:= "ifeq";
	op[opc_ifne]		:= "ifne";
	op[opc_iflt]		:= "iflt";
	op[opc_ifge]		:= "ifge";
	op[opc_ifgt]		:= "ifgt";
	op[opc_ifle]		:= "ifle";
	op[opc_if_icmpeq]	:= "if_icmpeq";
	op[opc_if_icmpne]	:= "if_icmpne";
	op[opc_if_icmplt]	:= "if_icmplt";
	op[opc_if_icmpge]	:= "if_icmpge";
	op[opc_if_icmpgt]	:= "if_icmpgt";
	op[opc_if_icmple]	:= "if_icmple";
	op[opc_if_acmpeq]	:= "if_acmpeq";
	op[opc_if_acmpne]	:= "if_acmpne";
	op[opc_goto]		:= "goto";
	op[opc_jsr]		:= "jsr";
	op[opc_ret]		:= "ret";
	op[opc_tableswitch]	:= "tableswitch";
	op[opc_lookupswitch]	:= "lookupswitch";
	op[opc_ireturn]		:= "ireturn";
	op[opc_lreturn]		:= "lreturn";
	op[opc_freturn]		:= "freturn";
	op[opc_dreturn]		:= "dreturn";
	op[opc_areturn]		:= "areturn";
	op[opc_return]		:= "return";
	op[opc_getstatic]	:= "getstatic";
	op[opc_putstatic]	:= "putstatic";
	op[opc_getfield]	:= "getfield";
	op[opc_putfield]	:= "putfield";
	op[opc_invokevirtual]	:= "invokevirtual";
	op[opc_invokespecial]	:= "invokespecial";
	op[opc_invokestatic]	:= "invokestatic";
	op[opc_invokeinterface]	:= "invokeinterface";
	op[opc_xxxunusedxxx]	:= "xxxunusedxxx";
	op[opc_new]		:= "new";
	op[opc_newarray]	:= "newarray";
	op[opc_anewarray]	:= "anewarray";
	op[opc_arraylength]	:= "arraylength";
	op[opc_athrow]		:= "athrow";
	op[opc_checkcast]	:= "checkcast";
	op[opc_instanceof]	:= "instanceof";
	op[opc_monitorenter]	:= "monitorenter";
	op[opc_monitorexit]	:= "monitorexit";
	op[opc_wide]		:= "wide";
	op[opc_multianewarray]	:= "multianewarray";
	op[opc_ifnull]		:= "ifnull";
	op[opc_ifnonnull]	:= "ifnonnull";
	op[opc_goto_w]		:= "goto_w";
	op[opc_jsr_w]		:= "jsr_w";
	op[opc_breakpoint] 	:= "breakpoint";

	dl[opc_nop] 		:= 0;
	dl[opc_aconst_null]	:= 1;
	dl[opc_iconst_m1]	:= 1;
	dl[opc_iconst_0]	:= 1;
	dl[opc_iconst_1]	:= 1;
	dl[opc_iconst_2]	:= 1;
	dl[opc_iconst_3]	:= 1;
	dl[opc_iconst_4]	:= 1;
	dl[opc_iconst_5]	:= 1;
	dl[opc_lconst_0]	:= 2;
	dl[opc_lconst_1]	:= 2;
	dl[opc_fconst_0]	:= 1;
	dl[opc_fconst_1]	:= 1;
	dl[opc_fconst_2]	:= 1;
	dl[opc_dconst_0]	:= 2;
	dl[opc_dconst_1]	:= 2;
	dl[opc_bipush]		:= 1;
	dl[opc_sipush]		:= 1;
	dl[opc_ldc]		:= 1;
	dl[opc_ldc_w]		:= 1;
	dl[opc_ldc2_w]		:= 2;
	dl[opc_iload]		:= 1;
	dl[opc_lload]		:= 2;
	dl[opc_fload]		:= 1;
	dl[opc_dload]		:= 2;
	dl[opc_aload]		:= 1;
	dl[opc_iload_0]		:= 1;
	dl[opc_iload_1]		:= 1;
	dl[opc_iload_2]		:= 1;
	dl[opc_iload_3]		:= 1;
	dl[opc_lload_0]		:= 2;
	dl[opc_lload_1]		:= 2;
	dl[opc_lload_2]		:= 2;
	dl[opc_lload_3]		:= 2;
	dl[opc_fload_0]		:= 1;
	dl[opc_fload_1]		:= 1;
	dl[opc_fload_2]		:= 1;
	dl[opc_fload_3]		:= 1;
	dl[opc_dload_0]		:= 2;
	dl[opc_dload_1]		:= 2;
	dl[opc_dload_2]		:= 2;
	dl[opc_dload_3]		:= 2;
	dl[opc_aload_0]		:= 1;
	dl[opc_aload_1]		:= 1;
	dl[opc_aload_2]		:= 1;
	dl[opc_aload_3]		:= 1;
	dl[opc_iaload]		:= -1;		(* pop 2, push 1 *)
	dl[opc_laload]		:= 0;		(* pop 2, push 2 *)
	dl[opc_faload]		:= -1;		(* pop 2, push 1 *)
	dl[opc_daload]		:= 0;		(* pop 2, push 2 *)
	dl[opc_aaload]		:= -1;		(* pop 2, push 1 *)
	dl[opc_baload]		:= -1;		(* pop 2, push 1 *)
	dl[opc_caload]		:= -1;		(* pop 2, push 1 *)
	dl[opc_saload]		:= -1;		(* pop 2, push 1 *)
	dl[opc_istore]		:= -1;
	dl[opc_lstore]		:= -2;
	dl[opc_fstore]		:= -1;
	dl[opc_dstore]		:= -2;
	dl[opc_astore]		:= -1;
	dl[opc_istore_0]	:= -1;
	dl[opc_istore_1]	:= -1;
	dl[opc_istore_2]	:= -1;
	dl[opc_istore_3]	:= -1;
	dl[opc_lstore_0]	:= -2;
	dl[opc_lstore_1]	:= -2;
	dl[opc_lstore_2]	:= -2;
	dl[opc_lstore_3]	:= -2;
	dl[opc_fstore_0]	:= -1;
	dl[opc_fstore_1]	:= -1;
	dl[opc_fstore_2]	:= -1;
	dl[opc_fstore_3]	:= -1;
	dl[opc_dstore_0]	:= -2;
	dl[opc_dstore_1]	:= -2;
	dl[opc_dstore_2]	:= -2;
	dl[opc_dstore_3]	:= -2;
	dl[opc_astore_0]	:= -1;
	dl[opc_astore_1]	:= -1;
	dl[opc_astore_2]	:= -1;
	dl[opc_astore_3]	:= -1;
	dl[opc_iastore]		:= -3;
	dl[opc_lastore]		:= -4;
	dl[opc_fastore]		:= -3;
	dl[opc_dastore]		:= -4;
	dl[opc_aastore]		:= -3;
	dl[opc_bastore]		:= -3;
	dl[opc_castore]		:= -3;
	dl[opc_sastore]		:= -3;
	dl[opc_pop]		:= -1;
	dl[opc_pop2]		:= -2;
	dl[opc_dup]		:= 1;
	dl[opc_dup_x1]		:= 1;
	dl[opc_dup_x2]		:= 1;
	dl[opc_dup2]		:= 2;
	dl[opc_dup2_x1]		:= 2;
	dl[opc_dup2_x2]		:= 2;
	dl[opc_swap]		:= 0;
	dl[opc_iadd]		:= -1;
	dl[opc_ladd]		:= -2;
	dl[opc_fadd]		:= -1;
	dl[opc_dadd]		:= -2;
	dl[opc_isub]		:= -1;
	dl[opc_lsub]		:= -2;
	dl[opc_fsub]		:= -1;
	dl[opc_dsub]		:= -2;
	dl[opc_imul]		:= -1;
	dl[opc_lmul]		:= -2;
	dl[opc_fmul]		:= -1;
	dl[opc_dmul]		:= -2;
	dl[opc_idiv]		:= -1;
	dl[opc_ldiv]		:= -2;
	dl[opc_fdiv]		:= -1;
	dl[opc_ddiv]		:= -2;
	dl[opc_irem]		:= -1;
	dl[opc_lrem]		:= -2;
	dl[opc_frem]		:= -1;
	dl[opc_drem]		:= -2;
	dl[opc_ineg]		:= 0;
	dl[opc_lneg]		:= 0;
	dl[opc_fneg]		:= 0;
	dl[opc_dneg]		:= 0;
	dl[opc_ishl]		:= -1;
	dl[opc_lshl]		:= -1;
	dl[opc_ishr]		:= -1;
	dl[opc_lshr]		:= -1;
	dl[opc_iushr]		:= -1;
	dl[opc_lushr]		:= -1;
	dl[opc_iand]		:= -1;
	dl[opc_land]		:= -2;
	dl[opc_ior]		:= -1;
	dl[opc_lor]		:= -2;
	dl[opc_ixor]		:= -1;
	dl[opc_lxor]		:= -2;
	dl[opc_iinc]		:= 0;
	dl[opc_i2l]		:= 1;
	dl[opc_i2f]		:= 0;
	dl[opc_i2d]		:= 1;
	dl[opc_l2i]		:= -1;
	dl[opc_l2f]		:= -1;
	dl[opc_l2d]		:= 0;
	dl[opc_f2i]		:= 0;
	dl[opc_f2l]		:= 1;
	dl[opc_f2d]		:= 1;
	dl[opc_d2i]		:= -1;
	dl[opc_d2l]		:= 0;
	dl[opc_d2f]		:= -1;
	dl[opc_i2b]		:= 0;
	dl[opc_i2c]		:= 0;
	dl[opc_i2s]		:= 0;
	dl[opc_lcmp]		:= -3;
	dl[opc_fcmpl]		:= -1;
	dl[opc_fcmpg]		:= -1;
	dl[opc_dcmpl]		:= -3;
	dl[opc_dcmpg]		:= -3;
	dl[opc_ifeq]		:= -1;
	dl[opc_ifne]		:= -1;
	dl[opc_iflt]		:= -1;
	dl[opc_ifge]		:= -1;
	dl[opc_ifgt]		:= -1;
	dl[opc_ifle]		:= -1;
	dl[opc_if_icmpeq]	:= -2;
	dl[opc_if_icmpne]	:= -2;
	dl[opc_if_icmplt]	:= -2;
	dl[opc_if_icmpge]	:= -2;
	dl[opc_if_icmpgt]	:= -2;
	dl[opc_if_icmple]	:= -2;
	dl[opc_if_acmpeq]	:= -2;
	dl[opc_if_acmpne]	:= -2;
	dl[opc_goto]		:= 0;
	dl[opc_jsr]		:= 1;
	dl[opc_ret]		:= 0;
	dl[opc_tableswitch]	:= -1;
	dl[opc_lookupswitch]	:= -1;
	dl[opc_ireturn]		:= -1;		(* don't care ? *)
	dl[opc_lreturn]		:= -2;		(* don't care ? *)
	dl[opc_freturn]		:= -1;		(* don't care ? *)
	dl[opc_dreturn]		:= -2;		(* don't care ? *)
	dl[opc_areturn]		:= -1;		(* don't care ? *)
	dl[opc_return]		:= 0;		(* don't care ? *)

	(* Defaults for single word load/store		     short Vs long *)
	dl[opc_getstatic]	:= 1;		(* Special case  1 or  2 *)
	dl[opc_putstatic]	:= -1;		(* Special case -1 or -2 *)
	dl[opc_getfield]	:= 0;		(* Special case  0 or  1 *)
	dl[opc_putfield]	:= -2;		(* Special case -2 or -3 *)

	dl[opc_invokevirtual]	:= 0;		(* Special case *)
	dl[opc_invokespecial]	:= -1;		(* Special case *)
	dl[opc_invokestatic]	:= 0;		(* Special case *)
	dl[opc_invokeinterface]	:= 0;		(* Special case *)
	dl[opc_xxxunusedxxx]	:= 0;
	dl[opc_new]		:= 1;
	dl[opc_newarray]	:= 0;
	dl[opc_anewarray]	:= 0;
	dl[opc_arraylength]	:= 0;
	dl[opc_athrow]		:= -1;		(* don't care *)
	dl[opc_checkcast]	:= 0;
	dl[opc_instanceof]	:= 0;
	dl[opc_monitorenter]	:= -1;
	dl[opc_monitorexit]	:= -1;
	dl[opc_wide]		:= 0;
	dl[opc_multianewarray]	:= 0;		(* Special case (1-dim#) *)
	dl[opc_ifnull]		:= -1;
	dl[opc_ifnonnull]	:= -1;
	dl[opc_goto_w]		:= 0;
	dl[opc_jsr_w]		:= 1;
	dl[opc_breakpoint] 	:= 0;

END JVMcodes.
(* ============================================================ *)
