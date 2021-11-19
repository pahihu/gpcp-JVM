(*  This is a suite of benchmarks that are relatively short, both in program
    size and execution time.  It requires no input, and prints the execution
    time for each program, using the system- dependent routine Getclock,
    below, to find out the current CPU time.  It does a rudimentary check to
    make sure each program gets the right output.  These programs were
    gathered by John Hennessy and modified by Peter Nye.
    Oberon: J.Templ 26.2.90 *)

(* Modifications
	98.05.01	--	(bsmith@cs.oberlin.edu)
	1. No longer imports SYSTEM.
	2. Performs Each test 100 times instead of the previous 10 (CONST repetitions)
	3. Properly handles implementations with different Input.TimeUnit values.
	4. Defined the procedure WriteReal, which may need to be modified under
	versions other than System-3. (Texts.WriteRealFix has a different interface
	in V4 than in System-3
	
	98.0518	--	(bsmith@cs.oberlin.edu)
	1. Parameters iy and yfl of Uniform11 are now VAR parameters. Without this
	change the procedure is a NoOp.
	2. Now performs 4 sets of each test. (number of repititions per set determined by
	the constant repetitions.) Prints figures in five columns, four results, last column is
	the mean.
*)

(* Ported to Component Pascal 2000.07.12/kjg
 *)

MODULE Hennessy;

IMPORT RTS, Console, CPmain;

CONST
	
	reps       = 1000;

	(* Towers *)
	maxcells   = 18;
	stackrange =  3;

	(* Intmm, Mm *)
	rowsize    = 40;

	(* Puzzle *)
	size       = 511;
	kindmax    = 3;
	typemax    = 12;
	d          = 8;

	(* Bubble, Quick *)
	sortElementObjects = 5000;
	srtElementObjects  = 500;

	(* Perm *)
	permrange  = 10;

TYPE
	(* tree *)
	NodeObject = POINTER TO RECORD
			val: INTEGER;
			left: NodeObject;
			right: NodeObject;
		     END;
	
	(* Towers *)
	ElementObject = POINTER TO RECORD
			  discsize: INTEGER;
			  next: INTEGER;
		        END;
	
  (* Intmm *) 
	IntMatrix = ARRAY rowsize+1, rowsize+1 OF INTEGER;

  (*
  (* Puzzle *) 
	Proc = PROCEDURE;
   *)
	
VAR
    (* global *)
	seed : INTEGER;
	ix   : INTEGER;
	jx   : INTEGER;
	t0   : LONGINT;
	t1   : LONGINT;
	t2   : LONGINT;
	t3   : LONGINT;

    (* Perm *) 
	permarray: ARRAY permrange+1 OF INTEGER;
	pctr: INTEGER;

    (* tree *)
	tree: NodeObject;

	(* Towers *)
	stack: POINTER TO ARRAY OF INTEGER;
	cellspace: POINTER TO ARRAY OF ElementObject;
	freelist: INTEGER;
	movesdone: INTEGER;

	(* Intmm *)
	ima, imb, imr: IntMatrix;

	(* Puzzle *)
	piececount: POINTER TO ARRAY OF INTEGER;
	kind, piecemax: POINTER TO ARRAY OF INTEGER;
	puzzl: POINTER TO ARRAY OF BOOLEAN;
	p: POINTER TO ARRAY OF ARRAY OF BOOLEAN;
	n: INTEGER;
	kount: INTEGER;

	(* Bubble, Quick *)
	sortlist: POINTER TO ARRAY OF INTEGER;
    
  biggest: INTEGER; 
  littlest: INTEGER;
  top: INTEGER;


(* global procedures *)

PROCEDURE Str*(s: ARRAY OF CHAR);
BEGIN
	Console.WriteString(s);
END Str;

PROCEDURE Initrand ();
BEGIN seed := 74755
END Initrand;

PROCEDURE Rand (): INTEGER;
BEGIN
    seed := (seed * 1309 + 13849) MOD 65535;
    RETURN (seed);
END Rand;


    (* Permutation program, heavily recursive, written by Denny Brown. *)
	
	PROCEDURE Swap (VAR a,b: INTEGER);
		VAR t: INTEGER;
	BEGIN 
	  t := a;  a := b;  b := t;
	END Swap;
	
	PROCEDURE Initialize ();
		VAR i: INTEGER;
	BEGIN i := 1;
		WHILE i <= 7 DO
			permarray[i] := i-1;
			INC(i)
		END
	END Initialize;
	
	PROCEDURE Permute (n: INTEGER);
		VAR k: INTEGER;
	BEGIN
		pctr := pctr + 1;
		IF ( n#1 ) THEN
			Permute(n-1);
			k := n-1;
			WHILE k >= 1 DO
				Swap(permarray[n], permarray[k]);
				Permute(n-1);
				Swap(permarray[n], permarray[k]);
				DEC(k)
			END
       END
	END Permute;
	
PROCEDURE Perm* ();
	VAR i: INTEGER;
BEGIN
	pctr := 0; i := 1;
	WHILE i <= 5 DO
		Initialize();
		Permute(7);
		INC(i)
	END ;
	IF ( pctr # 43300 ) THEN Str(" Error in Perm.$") END
END Perm;


    (*  Program to Solve the Towers of Hanoi *)

	PROCEDURE Makenull (s: INTEGER);
	BEGIN 
		stack[s] := 0
	END Makenull;

	PROCEDURE GetElementObject (): INTEGER;
		VAR temp: INTEGER;
	BEGIN
		IF ( freelist>0 ) THEN
			temp := freelist;
			freelist := cellspace[freelist].next;
		ELSE
			temp := 0;
			Str("out of space   $")
		END ;
		RETURN (temp);
	END GetElementObject;
	
	PROCEDURE Push(i,s: INTEGER);
        VAR localel: INTEGER; errorfound: BOOLEAN;
	BEGIN
		errorfound := FALSE;
		IF ( stack[s] > 0 ) THEN
			IF ( cellspace[stack[s]].discsize<=i ) THEN
				errorfound := TRUE;
				Str("disc size error$")
			END 
		END ;
		IF ( ~ errorfound ) THEN
			localel := GetElementObject();
			cellspace[localel].next := stack[s];
			stack[s] := localel;
			cellspace[localel].discsize := i
		END
	END Push;
	
	PROCEDURE Init (s,n: INTEGER);
		VAR discctr: INTEGER;
	BEGIN
		Makenull(s); discctr := n;
		WHILE discctr >= 1 DO
			Push(discctr,s);
			DEC(discctr)
		END
	END Init;

	PROCEDURE Pop (s: INTEGER; OUT result: INTEGER);
		VAR temp, temp1: INTEGER;
	BEGIN
		IF ( stack[s] > 0 ) THEN
			temp1 := cellspace[stack[s]].discsize;
			temp := cellspace[stack[s]].next;
			cellspace[stack[s]].next := freelist;
			freelist := stack[s];
			stack[s] := temp;
			result := temp1;
		ELSE
			result := 0;
			Str("nothing to pop $")
		END
	END Pop;

	PROCEDURE Move (s1,s2: INTEGER);
	VAR result: INTEGER;
	BEGIN
		Pop(s1, result);
		Push(result, s2);
		movesdone := movesdone+1;
	END Move;

	PROCEDURE tower(i,j,k: INTEGER);
		VAR other: INTEGER;
	BEGIN
		IF ( k=1 ) THEN
			Move(i,j);
		ELSE
			other := 6-i-j;
			tower(i,other,k-1);
			Move(i,j);
			tower(other,j,k-1)
		END
	END tower;

PROCEDURE Towers* ();
	VAR i: INTEGER;
BEGIN 
	i := 1;
	WHILE i <= maxcells DO cellspace[i].next := i-1; INC(i) END ;
	freelist := maxcells;
	Init(1,14);
	Makenull(2);
	Makenull(3);
	movesdone := 0;
	tower(1,2,14);
	IF ( movesdone # 16383 ) THEN Str(" Error in Towers.$") END
END Towers;


    (* The eight queens problem, solved 50 times. *)
(*
  type
      doubleboard =   2..16;
      doublenorm  =   -7..7;
      boardrange  =   1..8;
      aarray      =   array [boardrange] of boolean;
      barray      =   array [doubleboard] of boolean;
      carray      =   array [doublenorm] of boolean;
      xarray      =   array [boardrange] of boardrange;
*)

	(* dependant upon reference semantics of ARRAY * OF T ! *)

	PROCEDURE Try(i: INTEGER; OUT q: BOOLEAN; VAR a, b, c: ARRAY OF BOOLEAN; VAR x: ARRAY OF INTEGER);
    	VAR j: INTEGER;
	BEGIN
		j := 0;
		q := FALSE;
		WHILE (~q) & (j # 8) DO
			j := j + 1;
			q := FALSE;
			IF b[j] & a[i+j] & c[i-j+7] THEN
				x[i] := j;
				b[j] := FALSE;
				a[i+j] := FALSE;
				c[i-j+7] := FALSE;
				IF i < 8 THEN
					Try(i+1,q,a,b,c,x);
					IF ~q THEN
						b[j] := TRUE;
						a[i+j] := TRUE;
						c[i-j+7] := TRUE
					END
     	   	ELSE q := TRUE
				END
			END
		END
	END Try;

	PROCEDURE Doit ();
		VAR i: INTEGER; q: BOOLEAN;
			a: ARRAY 9 OF BOOLEAN;
			b: ARRAY 17 OF BOOLEAN;
			c: ARRAY 15 OF BOOLEAN;
			x: ARRAY 9 OF INTEGER;
	BEGIN
		i := 0 - 7;
		WHILE i <= 16 DO
			IF (i >= 1) & (i <= 8) THEN a[i] := TRUE END ;
			IF i >= 2 THEN b[i] := TRUE END ;
			IF i <= 7 THEN c[i+7] := TRUE END ;
			i := i + 1;
		END ;
		Try(1, q, b, a, c, x);
		IF ( ~ q ) THEN Str(" Error in Queens.$") END
	END Doit;

PROCEDURE Queens* ();
	VAR i: INTEGER;
BEGIN i := 1;
	WHILE i <= 50 DO Doit(); INC(i) END
END Queens;


    (* Multiplies two integer matrices. *)

	PROCEDURE Initmatrix (VAR m: IntMatrix);
		VAR temp, i, j: INTEGER;
	BEGIN i := 1;
		WHILE i <= rowsize DO
			j := 1;
			WHILE j <= rowsize DO
				temp := Rand();
				m[i][j] := temp - (temp DIV 120)*120 - 60;
				INC(j)
			END ;
			INC(i)
		END
	END Initmatrix;

	PROCEDURE Innerproduct(VAR result: INTEGER; 
			       IN  a,b: IntMatrix; 
			       row,column: INTEGER);
		VAR i: INTEGER;
  (* computes the inner product of A[row,*] and B[*,column] *)
	BEGIN
		result := 0; i := 1;
		WHILE i <= rowsize DO 
		  result := result+a[row][i]*b[i][column]; INC(i) 
		END
	END Innerproduct;

PROCEDURE Intmm* ();
	VAR i, j: INTEGER;
BEGIN
	Initrand();
	Initmatrix (ima);
	Initmatrix (imb);
	i := 1;
	WHILE i <= rowsize DO j := 1;
		WHILE j <= rowsize DO Innerproduct(imr[i][j],ima,imb,i,j); INC(j) END ;
		INC(i)
	END
END Intmm;



    (* A compute-bound program from Forest Baskett. *)

	PROCEDURE Fit (i, j: INTEGER): BOOLEAN;
		VAR k: INTEGER;
	BEGIN k := 0;
		WHILE k <= piecemax[i] DO
			IF ( p[i][k] ) THEN 
				IF ( puzzl[j+k] ) THEN 
					RETURN FALSE 
				END 
			END;
			INC(k)
		END;
		RETURN TRUE
	END Fit;
	
	PROCEDURE Place (i, j: INTEGER): INTEGER;
		VAR k: INTEGER;
	BEGIN k := 0;
		WHILE k <= piecemax[i] DO
			IF ( p[i][k] ) THEN puzzl[j+k] := TRUE END;
			INC(k)
		END;
		piececount[kind[i]] := piececount[kind[i]] - 1;
		k := j;
		WHILE k <= size DO
			IF ( ~ puzzl[k] ) THEN RETURN (k) END;
			INC(k)
		END ;
		RETURN (0);
	END Place;
	
	PROCEDURE Remove (i, j: INTEGER);
		VAR k: INTEGER;
	BEGIN k := 0;
		WHILE k <= piecemax[i] DO
			IF ( p[i][k] ) THEN puzzl[j+k] := FALSE END;
			INC(k)
		END;
		piececount[kind[i]] := piececount[kind[i]] + 1
	END Remove;
	
	PROCEDURE Trial (j: INTEGER): BOOLEAN;
		VAR i, k: INTEGER;
	BEGIN i := 0;
		kount := kount + 1;
		WHILE i <= typemax DO
			IF ( piececount[kind[i]] # 0 ) THEN
				IF ( Fit (i, j) ) THEN
					k := Place (i, j);
					IF Trial(k) OR (k = 0) THEN RETURN (TRUE)
					ELSE Remove (i, j)
					END;
				END
			END;
			INC(i)
		END;
		RETURN (FALSE)
	END Trial;
	
PROCEDURE Puzzle* ();
	VAR i, j, k, m: INTEGER;
BEGIN
	m := 0; WHILE m <= size DO puzzl[m] := TRUE; INC(m) END ;
	i := 1;
	WHILE i <= 5 DO j := 1;
		WHILE j <= 5 DO k := 1;
			WHILE k <= 5 DO
				puzzl[i+d*(j+d*k)] := FALSE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	
	i := 0; 
	WHILE i <= typemax DO m := 0;
		WHILE m<= size DO
			p[i][m] := FALSE; INC(m)
		END;
		INC(i)
	END;
	
	i := 0;
	WHILE i <= 3 DO j := 0;
		WHILE j <= 1 DO k := 0;
			WHILE k <= 0 DO
				p[0][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[0] := 0;
	piecemax[0] := 3+d*1+d*d*0;
	
	i := 0;
	WHILE i <= 1 DO j := 0;
		WHILE j <= 0 DO k := 0;
			WHILE k <= 3 DO
				p[1][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[1] := 0;
	piecemax[1] := 1+d*0+d*d*3;
	
	i := 0;
	WHILE i <= 0 DO j := 0;
		WHILE j <= 3 DO k := 0;
			WHILE k <= 1 DO
				p[2][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[2] := 0;
	piecemax[2] := 0+d*3+d*d*1;
	
	i := 0;
	WHILE i <= 1 DO j := 0;
		WHILE j <= 3 DO k := 0;
			WHILE k <= 0 DO
				p[3][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[3] := 0;
	piecemax[3] := 1+d*3+d*d*0;

	i := 0;
	WHILE i <= 3 DO j := 0;
		WHILE j <= 0 DO k := 0;
			WHILE k <= 1 DO
				p[4][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[4] := 0;
	piecemax[4] := 3+d*0+d*d*1;
	
	i := 0;
	WHILE i <= 0 DO j := 0;
		WHILE j <= 1 DO k := 0;
			WHILE k <= 3 DO
				p[5][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[5] := 0;
	piecemax[5] := 0+d*1+d*d*3;
	
	i := 0;
	WHILE i <= 2 DO j := 0;
		WHILE j <= 0 DO k := 0;
			WHILE k <= 0 DO
				p[6][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[6] := 1;
	piecemax[6] := 2+d*0+d*d*0;
	
	i := 0;
	WHILE i <= 0 DO j := 0;
		WHILE j <= 2 DO k := 0;
			WHILE k <= 0 DO
				p[7][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[7] := 1;
	piecemax[7] := 0+d*2+d*d*0;
	
	i := 0;
	WHILE i <= 0 DO j := 0;
		WHILE j <= 0 DO k := 0;
			WHILE k <= 2 DO
				p[8][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[8] := 1;
    piecemax[8] := 0+d*0+d*d*2;
	
	i := 0;
	WHILE i <= 1 DO j := 0;
		WHILE j <= 1 DO k := 0;
			WHILE k <= 0 DO
				p[9][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[9] := 2;
	piecemax[9] := 1+d*1+d*d*0;
	
	i := 0;
	WHILE i <= 1 DO j := 0;
		WHILE j <= 0 DO k := 0;
			WHILE k <= 1 DO
				p[10][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[10] := 2;
	piecemax[10] := 1+d*0+d*d*1;
	
	i := 0;
	WHILE i <= 0 DO j := 0;
		WHILE j <= 1 DO k := 0;
			WHILE k <= 1 DO
				p[11][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[11] := 2;
	piecemax[11] := 0+d*1+d*d*1;
	
	i := 0;
	WHILE i <= 1 DO j := 0;
		WHILE j <= 1 DO k := 0;
			WHILE k <= 1 DO
				p[12][i+d*(j+d*k)] := TRUE; INC(k)
			END;
			INC(j)
		END;
		INC(i)
	END;
	kind[12] := 3;
	piecemax[12] := 1+d*1+d*d*1;
	
	piececount[0] := 13;
	piececount[1] := 3;
	piececount[2] := 1;
	piececount[3] := 1;
	m := 1+d*(1+d*1);
	kount := 0;
	IF Fit(0, m) THEN n := Place(0, m)
	ELSE Str("Error1 in Puzzle$")
	END;
	IF ~ Trial(n) THEN Str("Error2 in Puzzle.$")
	ELSIF kount # 2005 THEN Str("Error3 in Puzzle.$")
	END
END Puzzle;


   (* Sorts an array using quicksort *)

	PROCEDURE Initarr();
		VAR i, temp: INTEGER;
	BEGIN
		Initrand();
		biggest := 0; littlest := 0; i := 1;
		WHILE i <= sortElementObjects DO
			temp := Rand();
			sortlist[i] := temp - (temp DIV 100000)*100000 - 50000;
			IF sortlist[i] > biggest THEN biggest := sortlist[i]
			ELSIF sortlist[i] < littlest THEN littlest := sortlist[i]
			END ;
			INC(i)
		END
	END Initarr;

	PROCEDURE Quicksort(VAR a: ARRAY OF INTEGER; l,r: INTEGER);
  (* quicksort the array A from start to finish *)
		VAR i,j,x,w: INTEGER;
	BEGIN
		i:=l; j:=r;
		x:=a[(l+r) DIV 2];
		REPEAT
			WHILE a[i]<x DO i := i+1 END;
			WHILE x<a[j] DO j := j-1 END;
			IF i<=j THEN
				w := a[i];
				a[i] := a[j];
				a[j] := w;
				i := i+1;    j := j-1
			END ;
		UNTIL i > j;
		IF l<j THEN Quicksort(a,l,j) END;
		IF i<r THEN Quicksort(a,i,r) END
	END Quicksort;

PROCEDURE Quick*();
BEGIN
    Initarr();
    Quicksort(sortlist,1,sortElementObjects);
    IF (sortlist[1] # littlest) OR (sortlist[sortElementObjects] # biggest) THEN  Str( " Error in Quick.$") END ;
END Quick;


    (* Sorts an array using bubblesort *)

	PROCEDURE bInitarr();
		VAR i, temp: INTEGER;
	BEGIN
		Initrand();
		biggest := 0; littlest := 0; i := 1;
		WHILE i <= srtElementObjects DO
			temp := Rand();
			sortlist[i] := temp - (temp DIV 100000)*100000 - 50000;
			IF sortlist[i] > biggest THEN biggest := sortlist[i]
			ELSIF sortlist[i] < littlest THEN littlest := sortlist[i]
			END ;
			INC(i)
		END
	END bInitarr;

PROCEDURE Bubble*();
	VAR i, j: INTEGER;
BEGIN
	bInitarr();
	top:=srtElementObjects;
	WHILE top>1 DO
		i:=1;
		WHILE i<top DO
			IF sortlist[i] > sortlist[i+1] THEN
				j := sortlist[i];
				sortlist[i] := sortlist[i+1];
				sortlist[i+1] := j;
			END ;
			i:=i+1;
		END;
		top:=top-1;
	END;
	IF (sortlist[1] # littlest) OR (sortlist[srtElementObjects] # biggest) THEN Str("Error3 in Bubble.$") END ;
END Bubble;

  (* Sorts an array using treesort *)

	PROCEDURE tInitarr();
		VAR i, temp: INTEGER;
	BEGIN
		Initrand();
		biggest := 0; littlest := 0; i := 1;
		WHILE i <= sortElementObjects DO
			temp := Rand();
			sortlist[i] := temp - (temp DIV 100000)*100000 - 50000;
			IF sortlist[i] > biggest THEN biggest := sortlist[i]
			ELSIF sortlist[i] < littlest THEN littlest := sortlist[i]
			END ;
			INC(i)
		END
	END tInitarr;

	PROCEDURE CreateNodeObject (VAR t: NodeObject; n: INTEGER);
	BEGIN
    	NEW(t);
		t.left := NIL; t.right := NIL;
		t.val := n
	END CreateNodeObject;

	PROCEDURE Insert(n: INTEGER; t: NodeObject);
	(* insert n into tree *)
	BEGIN
		IF n > t.val THEN
			IF t.left = NIL THEN CreateNodeObject(t.left,n)
			ELSE Insert(n,t.left)
			END
		ELSIF n < t.val THEN
			IF t.right = NIL THEN CreateNodeObject(t.right,n)
			ELSE Insert(n,t.right)
			END
		END
	END Insert;

	PROCEDURE Checktree(p: NodeObject): BOOLEAN;
    (* check by inorder traversal *)
		VAR result: BOOLEAN;
	BEGIN
		result := TRUE;
		IF p.left # NIL THEN
			IF p.left.val <= p.val THEN result := FALSE;
			ELSE result := Checktree(p.left) & result
			END
		END ;
		IF  p.right # NIL THEN
			IF p.right.val >= p.val THEN result := FALSE;
			ELSE result := Checktree(p.right) & result
			END
		END;
		RETURN result
	END Checktree;

PROCEDURE Trees*();
	VAR i: INTEGER;
BEGIN
	tInitarr();
	NEW(tree);
	tree.left := NIL; tree.right:=NIL; tree.val:=sortlist[1];
	i := 2;
    WHILE i <= sortElementObjects DO
    	Insert(sortlist[i],tree);
    	INC(i)
    END;
	IF ~ Checktree(tree) THEN Str(" Error in Tree.$") END;
END Trees;


  PROCEDURE INIT*(); 
    VAR indx : INTEGER;
  BEGIN
    Console.WriteString("Hennessy integer benchmarks for Component Pascal.");
    Console.WriteInt(reps,0);
    Console.WriteString(" iterations");
    Console.WriteLn;
    NEW(stack, stackrange+1);
    NEW(cellspace, maxcells+1);
    NEW(piececount, kindmax+1);
    NEW(kind, typemax+1);
    NEW(piecemax, typemax+1);
    NEW(puzzl, size+1);
    NEW(p, typemax+1, size+1);
    NEW(sortlist, sortElementObjects+1);
    FOR indx := 0 TO maxcells DO 
      NEW(cellspace[indx]) 
    END;
  END INIT;

  PROCEDURE WriteFraction(t : LONGINT);
    VAR strg : ARRAY 32 OF CHAR;
  BEGIN
    RTS.RealToStr(t/1000, strg);
    Console.WriteString(strg);
  END WriteFraction;

  PROCEDURE Time(IN str : ARRAY OF CHAR; idx : INTEGER);
    VAR indx : INTEGER;
  BEGIN
    t1 := RTS.GetMillis();
    FOR indx := 1 TO reps DO
      CASE idx OF
      | 0 : Perm();
      | 1 : Towers();
      | 2 : Queens();
      | 3 : Intmm();
      | 4 : Puzzle();
      | 5 : Quick();
      | 6 : Bubble();
      | 7 : Trees();
      END;
    END;
    t2 := RTS.GetMillis();
    Console.WriteString(str);
    WriteFraction(t2-t1);
    Console.WriteLn;
  END Time;

BEGIN
(*
  Console.WriteString("Greetings!");
  Console.WriteLn;
 *)
  INIT();
  t0 := RTS.GetMillis();
  Time("Perm    ", 0);
  Time("Towers  ", 1);
  Time("Queens  ", 2);
  Time("Intmm   ", 3);
  Time("Puzzle  ", 4);
  Time("Quick   ", 5);
  Time("Bubble  ", 6);
  Time("Trees   ", 7);
  t3 := RTS.GetMillis();
  Console.WriteString("total   ");
  WriteFraction(t3-t0);
  Console.WriteLn;
END Hennessy.

