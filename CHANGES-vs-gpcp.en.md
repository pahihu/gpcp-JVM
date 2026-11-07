# Differences between gpcp-JVM and the original GPCP

A detailed description of the changes in files that were modified relative to the
original `../gpcp` project (version 1.4.07). Later changes made inside `../gpcp`
itself are not considered here.

General context: starting with JDK 9 `rt.jar` was removed, modules/`.jmod` files were
introduced, and the bytecode verifier became stricter; at the same time the project had
to run on Unix (Linux/macOS) with JDK 11/17. This gives four groups of changes: strict
stack-frame verification, `.jmod` support in j2cps, Unix paths/stdin, and build
dependency cleanup.

---

## 1. `sources/gpcp/AsmFrames.cp` — remove `L...;` from StackMapTable

**Before.** GPCP generates JVM bytecode through ASM 5.1. Starting with class-file
version Java 7 (and `versionDefault = "7"`) the JVM requires a `StackMapTable` — a map
of local-variable and operand-stack types at branch points. GPCP keeps these types in
the `FrameElement.state` and `dclTp` fields.

When parsing a method signature, `ParseSig` stores a **full descriptor** such as
`Ljava/lang/String;` in these fields. RTS function return types end up there too
(`procRetS[...] = "Ljava/lang/String;"`, `"Ljava/lang/Class;"`, etc.).

**The problem.** `EmitStackFrame` in `AsmUtil.cp` passes an array of these values to
ASM:

```java
thisMv.visitFrame(ASM.Opcodes.F_NEW, loclNum, loclArr, evalNum, evalArr);
```

For an object type ASM expects an **internal name** such as `java/lang/String` (or an
array descriptor such as `[Ljava/lang/String;`), not a field descriptor like
`Ljava/lang/String;`. ASM does not parse the string; it writes it literally as a class
name into the constant pool/`StackMapTable`. The result is the illegal class name
`"Ljava/lang/String;"`.

Java 7/8 were lenient here, but JDK 9+ (and especially 11/17) validate names in the
`StackMapTable` and fail at class load/verification with
`ClassFormatError`/`VerifyError` (illegal class name). Externally this looks like
"the class was compiled, but the new JVM refuses to load it".

**What was done.** A `remSigS` function was added:

```pascal
IF obj IS RTS.NativeString THEN
  sig := obj(RTS.NativeString);
  IF sig.startsWith("L") & sig.endsWith(";") THEN
    RETURN sig.substring( 1, sig.length()-1 );
  END;
END;
RETURN obj
```

That is, `Lpkg/Class;` → `pkg/Class`. Everything else is left untouched: ASM's
primitive codes (`INTEGER`, `FLOAT`, `LONG`, `TOP`, …), `NIL`, and arrays (`[L...;`,
`[I` — they start with `[`, not `L`).

The calls were added in three places — `GetLocalArr`, `GetDclTpArr`, `GetEvalArr` —
that is, **only when data is handed to ASM for frames**. The compiler's internal type
model is unchanged, so the generation of other instructions is unaffected.

Commits: `9c08641` (first version using a `CHAR` buffer), `0521945` (simplified to
`startsWith`/`substring`).

---

## 2. `sources/gpcp/Browse.cp` — let command-line modules be found through CPSYM

**Before.** Browse looks for a module first in the current directory
(`GPBinFiles.findLocal`), then in the directories from `CPSYM` (`findOnPath`). The flag
`mod.progArg = TRUE` is set for modules listed on the command line.

The old code:

```pascal
file := GPBinFiles.findLocal(mod.symName);
IF file = NIL THEN
  file := GPBinFiles.findOnPath("CPSYM", mod.symName);
  IF (file = NIL) OR (mod.progArg) THEN
    ... "not found" ... HALT(1)
```

So if a module was not in the current directory but **was found** via `CPSYM`, and it
had been specified on the command line, Browse still printed "File <...> not found" and
terminated.

**Why this matters for new JVMs.** The JDK 11/17 symbol files do not live next to the
user; they are in `symfiles/11/JvmSystem` and `symfiles/17/JvmSystem` and are reachable
only through `CPSYM`. Therefore a command such as `browse java_lang` (or browsing the
new symbol files from an arbitrary directory) was guaranteed to fail.

**What was done.** The `OR (mod.progArg)` condition was commented out:

```pascal
IF (file = NIL) (* OR (mod.progArg)) *) THEN
```

Now only a genuine "file not found" situation is fatal, and a module found via `CPSYM`
is processed normally. Commit `3ad8c16`.

---

## 3. `sources/gpcp/build.xml` — CPSYM path separator for Unix

**Before.** Ant passes the symbol-file path to the gpcp/CPMake/Browse JVM processes:

```xml
<jvmarg value="-DCPSYM=${CPSYM}"/>
```

`CPSYM` is a list of directories. The path-reading code (`GPFiles`/`GPBinFiles`) splits
it by `File.pathSeparator`, i.e. `:` on Unix and `;` on Windows.

The old value was Windows-style:

```xml
<property name="CPSYM" value=".;${JRoot}/symfiles;${JRoot}/symfiles/JvmSystem"/>
```

On Linux/macOS `;` is not a separator, so the whole string was treated as **one**
nonexistent path. The compiler could not find `java_lang.cps`, `java_util.cps`, etc.,
and could not compile a program against the JDK.

**What was done.** Replaced with the Unix form:

```xml
<property name="CPSYM" value=".:${JRoot}/symfiles:${JRoot}/symfiles/JvmSystem"/>
```

This is needed so that the `ant` build of gpcp and symbol-file regeneration work on
Unix with the new JDKs. Commit `3ad8c16`.

---

## 4. `sources/j2cps/ClassDesc.java` — classes inside a jmod live under `classes/`

**Before.** j2cps reads `.class` files and converts them to `.cps`. For each archive
entry it knows:

- `qualName` — the name derived from the entry path;
- `clName` — the real internal class name from the `this_class` constant-pool entry;
- `parentPkg.name` — the package derived from the path.

The consistency check was:

```java
if (!qualName.equals(clName)) {
  if (clName.startsWith(parentPkg.name)) { ... ok ... }
  else { ... "IS NOT PART OF PACKAGE" ... return false; }
}
```

**The problem.** A `.jmod` is a ZIP with a 4-byte `JM\x01\x00` header, and the classes
inside live in a `classes/` directory:

```
classes/module-info.class
classes/javax/annotation/processing/AbstractProcessor.class
```

So for the class `java/lang/Object`:
- `qualName` = `classes/java/lang/Object`;
- `parentPkg.name` = `classes/java/lang`;
- `clName` = `java/lang/Object`.

`clName.startsWith("classes/java/lang")` is false, so the class is considered "foreign"
to the package; j2cps prints an error, re-derives the package, and **returns false**,
i.e. the class is skipped.

**What was done.**

```java
String extClName = "classes/" + clName;
if (clName.startsWith(parentPkg.name) ||
    extClName.startsWith(parentPkg.name))
```

The comparison against `classes/java/lang/Object` succeeds. After that `qualName` is
normalized back to `clName` (`java/lang/Object`), so the resulting symbol files keep
normal names `java_lang`, `java_util`, rather than `classes_*`.

This is the key change without which the JDK 11/17 symbol files cannot be generated
from `.jmod` (and `rt.jar` no longer exists since JDK 9). Commit `5688ea0`.

---

## 5. `sources/j2cps/ConstantPool.java` — `CONSTANT_Module`/`CONSTANT_Package` tags

**Before.** The constant-pool parser knew tags up to `CONSTANT_InvokeDynamic` (18).
On an unknown tag it printed:

```
Unrecognized constant type: N
```

and threw `IOException`, after which j2cps terminated.

**The problem.** Class files from JDK 9+ contain two new tags:

- `CONSTANT_Module = 19`;
- `CONSTANT_Package = 20`.

They already occur in `module-info.class`, which is the **first** entry in every jmod
(`classes/module-info.class`). So j2cps failed on the very first class of a module and
could not process any `.jmod`.

**What was done.** Constants and handling were added:

```java
case CONSTANT_Module:
    return SkipInfo(this, tag, stream.readUnsignedShort(), 0);
case CONSTANT_Package:
    return SkipInfo(this, tag, stream.readUnsignedShort(), 0);
```

Both structures have a single `u2 name_index`, like `CONSTANT_Class`, so the same
`SkipInfo` is used. The actual contents of module/package entries are not needed for
generating `.cps`; it is enough to skip them correctly and continue parsing. Commit
`5688ea0`.

---

## 6. `sources/j2cps/PackageDesc.java` — strip the `classes_`/`classes.` prefix

**Before.** The package name is built from the path: `classes/java/lang` becomes:

- `cpName = "classes_java_lang"` — used as the Component Pascal module name and the
  `<cpName>.cps` file name;
- `javaName = "classes.java.lang"` — the Java name.

**The problem.** The resulting symbol files and modules would be named
`classes_java_lang`, `classes_java_util`, etc. As a result:

- `IMPORT java_lang;` in user code and the standard library would not find the module;
- the names would not match the expected ones (`java_lang`, `java_util`, …);
- JDK packages would be duplicated under "garbage" names.

**What was done.** Two helpers were added, each cutting off the first 8 characters:

```java
private String removeCLSU(String pName) {   // "classes_..." -> "..."
    if (pName.startsWith("classes_")) return pName.substring(8);
    return pName;
}
private String removeCLSDOT(String pName) { // "classes...." -> "..."
    if (pName.startsWith("classes.")) return pName.substring(8);
    return pName;
}
```

They are applied both in the anonymous-package constructor and in `MakeName`, i.e. to
`cpName` and `javaName` alike.

Empirical check: the current `jars/j2cps.jar` run on `java.compiler.jmod` produces
`javax_lang_model.cps`, `javax_tools.cps`, `javax_annotation_processing.cps`, etc. —
without `classes_*` (a separate `classes.cps` comes from `module-info.class`, which is
expected). Commit `5688ea0`.

---

## 7. `sources/j2cps/j2cps.java` — accept `.jmod` for `-jar`

**Before.** The argument check was:

```java
if (ClassDesc.useJar && !argStr.toLowerCase().endsWith(".jar")) {
    System.err.println("After -jar, filename must end \".jar\"");
    System.exit(1);
}
```

**The problem.** JDK 9+ is distributed as `.jmod` modules; the symbol-file generation
command looks like:

```sh
j2cps -dst JvmSystem -jar $JAVA_HOME/jmods/java.base.jmod
```

The old check rejected `.jmod` before even opening the file, so JDK 11/17 symbol files
could not be generated.

**What was done.**

```java
if (... !argStr.toLowerCase().endsWith(".jar") & !argStr.toLowerCase().endsWith(".jmod")) {
    System.err.println("After -jar, filename must end in \".jar\" or \".jmod\"");
```

The rest of the code needed no change: `JarFile` can read a jmod despite the 4-byte
header (verified — `JarFile` lists `classes/module-info.class`). `JarHandler` then
processes the entries like an ordinary zip. Commit `5688ea0`.

---

## 8. `sources/libs/java/GPBinFiles.java` — removed an unnecessary import

**Before.**

```java
import CP.ProgArgs.ProgArgs.*;
```

This is an import-on-demand **from a class**, not from a package. At the same time,
nothing from `ProgArgs` is used in `GPBinFiles` itself — the import is unused.

**Why it was removed.** It created an unnecessary dependency of the file I/O class
`GPBinFiles` on `CP.ProgArgs`. Runtime sources are compiled separately (`javac` per
file, see `MakeAll.bat`), and in the new layout/slim `cprts.jar` for Unix/JDK 11/17 such
a dependency is unnecessary and makes the build fragile: if `ProgArgs` is not visible at
that compilation step for any reason, `GPBinFiles` fails too, even though it does not
need `ProgArgs`. Commit `3ad8c16`.

One caveat: the comment in the file previously said "which is not present in the current
runtime library". Strictly speaking that is inaccurate — `CP/ProgArgs/ProgArgs.class` is
present in `jars/cprts.jar`. A more precise wording would be "unused import that creates
an unnecessary dependency".

---

## 9. `sources/libs/java/StdIn.java` — correct `More()` and EOF tracking

**Before.** In the Java implementation of `StdIn.cp`:

```java
public static boolean More() throws IOException {
    return true;         // temporary fix until we figure out
 // return rdr.ready();  // how to get the same semantics for
}                        // .NET and the JVM (kjg Sep. 2004)
```

That is, `More()` **always** returned `true`. `StdIn.cp` even documents this:
`(* Return TRUE in gpcp v1.3! *)`.

**The problem.** A typical input loop:

```pascal
WHILE StdIn.More() DO
  StdIn.ReadLn(line);
  ...
END;
```

If stdin is redirected from a file or a pipe, then after EOF `readLine()` returns
`null`, `ReadLn` yields an empty string, and `More()` keeps returning `true`, so the
loop becomes infinite. On an interactive terminal this was less noticeable, but in Unix
scripts (`bin/cprun`) and with piped input it shows up immediately.

**What was done.**

```java
private static boolean eof = false;
...
if (str == null) {
    eof = true;
    ...
}
...
public static boolean More() throws IOException {
 // return !eof;
 // return true;
    return rdr.ready();
}
```

- `eof` is set when `readLine()` returns `null`;
- `More()` now returns `rdr.ready()` — `false` when no new data is available and
  reading would block, so the loop terminates at EOF;
- the `return !eof` variant and the old `return true` are left commented out.

A subtlety: the `eof` field is currently not actually used (only in the commented-out
line); the real behavior change is `rdr.ready()`. Also, `ready()` is not a perfect EOF
test for an interactive terminal (it may return `false` before the first input arrives),
which is why the author left the alternatives in comments. But for redirected input and
pipes it fixes the infinite loop. Commit `3ad8c16` ("UNIX scripts, StdIn.More()").

---

## Summary of the changes

- **Strict JDK 11/17 verification:** `AsmFrames.cp` (valid names in StackMapTable).
- **JDK 9+ modules instead of `rt.jar`:** `j2cps.java`, `ClassDesc.java`,
  `ConstantPool.java`, `PackageDesc.java` (reading `.jmod`, `classes/`, tags 19/20,
  normal package names).
- **Unix environment:** `build.xml` (`CPSYM` separator), `Browse.cp` (finding
  command-line modules through `CPSYM`), `StdIn.java` (EOF on redirected input).
- **Build cleanliness:** `GPBinFiles.java` (unnecessary import).

Section 10 additionally documents the compiler-toolchain patches ported from
bbcb-fe (`sources/gpcp/*.cp`, 58 patches, ADR-012 ... ADR-238).

---

## 10. Ported compiler-toolchain patches (from bbcb-fe)

The 13 files below were changed to port the compiler fixes that
`../IdeaProjects/bbcb-fe` applies to its copy of GPCP. There the patches are
applied by `tools/gpcp/patch_toolchain.py`: the patched `.cp` sources are
recompiled into `build/toolchain-patch/` and prepended to the classpath, so
`gpcp.jar` itself is never modified. The same edits are now applied directly to
the sources in this repository, so a normal build picks them up.

Scope: **all 58 active patches** of `patch_toolchain.py` (the two entries marked
`"disabled": True` are not applied there either and are therefore not ported).

| File | ADR | What it fixes |
|---|---|---|
| `sources/gpcp/AsmUtil.cp` | 012 | `ARRAY OF SHORTCHAR` is described as `[C`, so allocate with `T_CHAR`; otherwise `VerifyError: Bad type on operand stack` |
| | 019 | `VarInit` emits a zero of the correct JVM category per type instead of `aconst_null` |
| | 067/072 | record classes (incl. `CP/$T/...`) are `ACC_PUBLIC`; otherwise `AbstractMethodError` when a private type overrides a public abstract method |
| | 072 | bridge method for covariant result narrowing (`New*(): Model` vs `New(): StdModel`) |
| `sources/gpcp/NewSymFileRW.cp` | 013 | do not set `D.noNew` on types read from symbol files (native types have a no-arg constructor) |
| | 044 | `falSy` only for real foreign records (`D.isFn`), so native interface records stay copyable |
| | 050 | `WalkImports` reads indirect (weak) imports recursively, with `res.host`; a missing `.cps` for a weak import is not an error |
| | 223 | a weak import never shadows an explicit alias/declaration |
| `sources/gpcp/Builtin.cp` | 224 | `SYSTEM.LSH` / `SYSTEM.ROT` bound in the SYSTEM scope (as in BlackBox) |
| `sources/gpcp/CPascalP.cp` | 224 | `IMPORT SYSTEM` allowed on the JVM without `/unsafe` |
| | 015 | `m.P^` super call to an implement-only (`P-`) method accepted |
| | 040 | temporary `WITH` variable of record type marked dynamic (bit 5 of `locAtt`) |
| | 043 | export of a field of a private record accepted (no error 183) |
| | 048 | type name entered into the scope before its body; unfilled type id = forward type |
| | 238 | text after `END <Module>.` is not scanned (avoids a scanner crash on non-ASCII text) |
| `sources/gpcp/CPascalErrors.cp` | 019/023/024/045 | errors 135/316/139/151/136 downgraded to warnings (both counter and "Error" label) |
| `sources/gpcp/JavaUtil.cp` | 019 | scalar locals initialized too |
| | 028/039 | local proxies of boxed OUT parameters initialized |
| | 042 | lazy generation of the wrapper class for a procedure-typed record field |
| | 056 | anonymous record bound to an id-less pointer gets an anonymous id |
| | 067 | anonymous procedure types get a structural name (`CP/$T/...`), so cross-module procedure assignments verify |
| `sources/gpcp/ExprDesc.cp` | 020 | empty set literal `{}` gets an explicit empty value |
| | 021 | unary minus on a set is complement (`-{}` = all bits) |
| | 046 | `coerceUp` of a real literal adopts the target real type |
| | 051 | CHAR literal accepted where a character array/string is expected |
| `sources/gpcp/IdDesc.cp` | 025 | `FINALIZE` does not require `NEW` (predeclared on `ANYPTR` in BlackBox) |
| | 040 | `isDynamic` honours the WITH-record marker |
| `sources/gpcp/TypeDesc.cp` | 041 | `ANYREC` is dynamically typed (`WITH msg: T DO` over `VAR msg: ANYREC`) |
| `sources/gpcp/JavaMaker.cp` | 047 | a function reaching `END` emits `PushJunkAndReturn` (also in `RESCUE`) |
| | 064 | `INC`/`DEC` on `LONGINT` pushes the increment in its own type and converts (`i2l`/`l2i`) |
| `sources/gpcp/Symbols.cp` | 049 | `IN` parameter is compatible by value (string literal for a fixed char array) |
| | 051 | CHAR literal assign-compatible with a character array |
| `sources/gpcp/CPascalS.cp` | 052 | `0A0X` (NBSP) treated as whitespace |
| | 180/188 | UTF-8 input decoded into CHAR buffers (1 MiB blocks), incomplete sequences carried across blocks |
| `sources/gpcp/AsmFrames.cp` | 027 | `ANYPTR`/`ANYREC` locals and IN parameters get the real JVM type instead of `TOP` |

Every touched file has a header comment that states who changed it and when
(`Modified in gpcp-JVM by nemavasi <nemavasi@yandex.ru>, 2026-11-06`), where the
patch came from (`../IdeaProjects/bbcb-fe/tools/gpcp/patch_toolchain.py`), and a
`Why:` / `What:` block; each individual edit is marked with its ADR number.

### Verification

- The patched sources are **code-identical** to what bbcb-fe's script compiles
  (comments stripped, whitespace normalized) - the port does not invent edits.
- All 13 files compile with the original `gpcp.jar` as bootstrap; the reference
  script builds 87 classes from them.
- The whole compiler builds from these sources: `CPMake` reports
  **44 modules compiled**, and a second, self-hosted stage (using the freshly
  built classes as the compiler) also succeeds.
- 18 small test modules exercise the fixes (15 of them are executable). With the
  unpatched compiler 14 of the 15 fail: 13 do not compile at all (errors 105,
  127, 135/136, 183, `NEW illegal ...`, `Cannot import SYSTEM ...`, or a
  compiler crash such as `ArrayIndexOutOfBoundsException` in
  `MutateEvalStack`), and `TShortChar` compiles but the JVM rejects the class
  with `VerifyError: Bad type on operand stack` (`[S` instead of `[C`). The one
  test that passes on both compilers is the covariant-override case, because in
  that construction GPCP already emits the base result descriptor, so no bridge
  is needed. With the patched compiler all 18 compile and all 15 run and print
  the expected result.

### Assessment

- **ADR-012 (SHORTCHAR), 019 (zeroed locals), 027 (frame types), 028/039 (OUT
  proxies), 047 (return at `END`), 064 (INC/DEC), 072 (bridges)** fix real
  bytecode/verifier defects. They only change generated code where the old code
  was invalid, so the risk is low and the effect is directly observable.
- **ADR-020/021 (sets), 046 (real literals)** fix silently wrong *values*
  (`-{}` = 0 instead of all bits). Correct and important, but semantic: code
  that relied on the wrong result would change behaviour.
- **ADR-025, 040, 041, 043, 049, 051, 223, 224, 238** only *accept more
  programs* (widen name lookup, argument compatibility, dynamic typing,
  visibility). They cannot change the bytecode of programs that already
  compiled, so they are safe; they do lower GPCP's strictness below the 1.4.07
  default, which is intentional for BlackBox compatibility.
- **ADR-044, 050** change symbol-file semantics: native interface records
  become copyable and indirect imports are read eagerly. This is a wider change
  - it can make the compiler read more `.cps` files (including ones that would
  previously stay opaque) and it depends on those files being present. In
  bbcb-fe this is the foundation for compiling BlackBox modules unchanged.
- **ADR-013** removes a safety check for `NEW` on extensions of native types. It
  is correct for JAVA-backed `SYSTEM MODULE` types (which always have a default
  constructor), but it also removes the diagnostic for genuinely constructor-less
  foreign types.
- **ADR-067** gives anonymous procedure types structural names. This changes
  generated class names (`CP/$T...`), so class files produced by the patched
  compiler are not binary-identical to the old ones; modules must be recompiled
  together, which is already the GPCP model.
- **ADR-180/188 (UTF-8 scanner)** is the largest single change: it rewrites
  `Reset` and enlarges the blocks to 1 MiB. It is independent of the rest, but
  it is the one most worth re-testing if the scanner is touched again.
- Overall: the port is faithful (same text as the tested upstream patch set),
  the compiler still bootstraps and self-hosts, and the observable defects are
  gone. The main residual risk is not in these edits but in their breadth:
  gpcp-JVM now behaves like the BlackBox-compatible compiler rather than like a
  stock 1.4.07 build, so error-severity and symbol-file expectations differ from
  upstream.

---

## 11. `sources/gpcp/JavaUtil.cp`, `JavaMaker.cp`, `ExprDesc.cp`, `StatDesc.cp` — procedure values (fixProcEqual)

**Before.** On the JVM a procedure value is a wrapper object (`Proc$Lit$N`), and a
fresh object was allocated for every evaluation of a literal. `=`/`#` compiled to
`if_acmpeq`/`if_acmpne`, i.e. wrapper references were compared. Consequently
`P = P` was `FALSE`, while `f = g` was `TRUE` only because both variables held the
same object. In addition, every named procedure type got its own host class, so
`H1 = H2` with matching signatures was `FALSE`, although the Component Pascal
report (Appendix A) makes such types **equal**.

**What changed.** Implemented the Kotlin **callable-reference** (`::f`,
`obj::m`) / .NET delegate model.  This is deliberately not the Kotlin
*lambda* model: `kotlin.jvm.internal.Lambda` does not override `equals`, so
plain lambdas compare by reference.  `FunctionReference.equals`, on the other
hand, compares owner, name, JVM signature, arity/flags and the **bound
receiver**.  A Component Pascal procedure value is always a reference to a
named procedure, so the `FunctionReference` analogue is the correct one.

- the compiler-generated `Proc$Lit$` wrapper implements
  `CP.CPJrts.ProcKey` and provides `procKey()` (`owner + "." + name +
  descriptor`), `procEnv()` (`NIL` on the strict branch), `equals(Object)` and
  `hashCode()`; equality is therefore shared by wrappers with different host
  classes;
- the host class of a procedure type keeps its original Java ABI.  In
  particular, named types declared in a `-special` interface keep
  `CP/<Mod>/<Mod>_<Type>` (`Kernel.Handler`, `Meta.CallWithProc`, …), and two
  such types with identical signatures stay distinct (`Kernel.Handler` vs
  `Kernel.Command`).  This is what hand-written platform bodies and their
  method descriptors expect;
- `DoCmp` emits `java/util/Objects.equals` for `Ty.Procedure` instead of
  `if_acmp*`; `NIL` is handled automatically;
- two procedure literals are folded during code generation
  (`ProcLitKey`/`sameKey`), so `P = P` creates no wrappers at all;
- a literal in a comparison is wrapped in the host class of the statically named
  operand (`BinCmp`), so both sides share a base class;
- ordinary (non-`-special`) modules give every equal signature one structural
  host class (`CP/$T/P...`), extending ADR-067 from anonymous to named types.
  A named type and an anonymous type with the same formal list are therefore
  the same JVM class, and values flow between them without casts.  Modules must
  be recompiled together (already the GPCP model);
- direct calls through an array element of procedure type (`a[i](x)`) are
  supported: `ExprDesc.liveActuals` and `JavaMaker.CheckCall` handle an
  indirect callee, and `getProcVarInvoke` creates the host class whenever it
  is missing (not only when `xName` is also NIL);
- `TypeOfBox` supports procedure types (a one-element array box), so functions
  with `VAR`/`OUT` procedure parameters work even when an explicit function
  result already occupies the JVM return slot.

**Strict CP policy.** This branch follows the Component Pascal report: a
procedure value may only be a named, non-local procedure.  Method values and
values of procedures local to another procedure are rejected at compile time
with error 165 (`This procedure cannot be used as a procedure value`) in
assignments, procedure-typed actual parameters, `RETURN` and `=`/`#`
comparisons.  The corresponding checks live in `ExprDesc.CheckProcValue` plus
its call sites in `ExprDesc` and `StatDesc`; the `strict_*` test cases cover
them.

**Tests.** `tests/gpcp/cases/proceq_*` (including the imported MIT oberonc cases
`proceq_ref_oberonc`, `procvars_ref_*`, `procsig_ref_equal`),
`proceq_regression`, `proceq_special_abi` (named `-special` host classes and
the `ProcKey` wrapper ABI), `array_proc_call`, `var_proc_param_function`,
`import_literal_named_type`, the `oberonc_*` general suite and the `strict_*`
cases (including method/field and nested/array); 78/78 cases pass on the
`fixProcEqual` branch.
