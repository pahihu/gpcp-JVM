# GPCP compiler regression tests

These tests cover the compiler-toolchain patches ported from `bbcb-fe` in
commit `f4966be` (see `CHANGES-vs-gpcp.en.md`, section 10).  They are small
Component Pascal modules that are compiled and, where useful, executed with the
compiler built from `sources/gpcp`.

The stock `jars/gpcp.jar` does **not** contain these patches.  The runner
therefore bootstraps the compiler from the patched sources first (with
`jars/gpcp.jar` and `jars/cpmake.jar`), exactly like `build.xml` does, and uses
the freshly built classes for the cases.

## Running

```bash
tests/gpcp/run-tests.sh
```

Requirements: a JDK on `PATH` (or `JAVA=...`), `python3` for the multi-block
UTF-8 case, and the jars already present in `jars/`.

Useful options:

```bash
tests/gpcp/run-tests.sh adr012 adr047   # only matching case names
KEEP=1 tests/gpcp/run-tests.sh          # keep the temporary build tree
```

The script prints `PASS`/`FAIL` per case and exits non-zero on any failure.
Temporary files go to `$TMPDIR` (or `/tmp`) and are removed afterwards.

## Case format

Each directory under `cases/` is one test:

| file | meaning |
|---|---|
| `*.cp` | sources; compiled in filename order unless `modules.txt` is present |
| `modules.txt` | explicit compile order (one module per line) |
| `special.txt` | modules to compile with `-special` (native `SYSTEM MODULE` interfaces) |
| `run.txt` | module to execute after compilation; run as `CP.<Module>.<Module>` |
| `expected.txt` | exact expected stdout of `run.txt`; without it the case is compile-only |
| `prepare.py` | optional generator run before compilation (used for the >1 MiB UTF-8 source) |

Cases are compiled with the patched compiler and `-nowarn`; a compile error is
a test failure.  Output is compared byte for byte.

## Coverage

| ADR | Case | What is checked |
|---|---|---|
| 012 | `adr012_shortchar` | module/local `ARRAY OF SHORTCHAR`, array parameter; no `VerifyError` |
| 013 | `adr013_044_native` | `NEW` on an extension of a native `SYSTEM MODULE` record |
| 019 | `adr019_init_locals` | scalar locals (integer, long, real, pointer, procedure) are zeroed |
| 020/021 | `adr020_021_sets` | `{}` value and `-{} = {0..31}` complement |
| 025 | `adr025_finalize` | `FINALIZE` redefinition without `NEW` |
| 027 | `adr027_anyptr` | `ANYPTR` local and `IN` parameter frame types |
| 028/039 | `adr028_039_outparams` | several boxed `OUT` proxies, including through a function result |
| 041 | `adr041_anyrec` | `WITH` type guard over a `VAR ...: ANYREC` parameter |
| 042 | `adr042_procfield` | call through a procedure-typed record field (lazy wrapper) |
| 043 | `adr043_private_field` | exported field of a private record (no error 183) |
| 044 | `adr013_044_native` | native interface record remains copyable |
| 046 | `adr046_real_literal` | `MIN`/`MAX(SHORTREAL)` and `MIN`/`MAX(REAL)` mix correctly |
| 047 | `adr047_func_end` | function falling through to `END` returns a value |
| 048 | `adr048_recursive_type` | type name visible in its own body (recursive `Node`) |
| 049 | `adr049_in_param` | string literal passed to a fixed `IN` character array |
| 050 | `adr050_indirect_import` | type from an indirect (weak) import resolves in the importer |
| 051 | `adr051_char_string` | `CHAR` literal in assignment, concatenation and parameter |
| 052 | `adr052_nbsp` | `0A0X` (NBSP) treated as whitespace |
| 056 | `adr056_anon_record` | anonymous record bound to an id-less pointer |
| 064 | `adr064_incdec` | `INC`/`DEC` on `LONGINT` with an `INTEGER` operand |
| 067 | `adr067_anon_proc` | anonymous procedure value passed between modules |
| 072 | `adr072_covariant` | covariant result override called through the base class |
| 180/188 | `adr180_utf8`, `adr180_utf8_big` | UTF-8 literals and a source spanning two scanner blocks |
| 223 | `adr223_weak_shadow` | weak import does not shadow an explicit declaration |
| 224 | `adr224_system` | `IMPORT SYSTEM` on the JVM, `SYSTEM.LSH` / `SYSTEM.ROT` |
| 238 | `adr238_after_end` | non-ASCII text after `END <Module>.` is not scanned |

## fixProcEqual (procedure values on the JVM)

These cases define the target semantics for procedure-value equality (the
Kotlin `FunctionReference` model: owner + name + signature + captured
environment).  They are the TDD baseline for the `fixProcEqual` branch and are
expected to **fail** until that change lands.  `proceq_regression` already
passes and must keep passing.

| Case | What is checked |
|---|---|
| `proceq_basic` | `=` / `#` on procedure values, `NIL`, literal-vs-literal, literal-vs-variable, calls through values |
| `proceq_fields_params` | values in record fields, arrays, value and `VAR` parameters |
| `proceq_cross` | values produced in one module compared in another; same name/signature but a different owner stays unequal |
| `proceq_named_types` | equal procedure types denoted by different type identifiers compare equal (CP report, Appendix A) |
| `proceq_regression` | pointer/string/CHAR/integer/REAL/SET comparisons keep their existing semantics |

### Imported reference cases (MIT)

The `*_ref_*` cases are adapted from **oberonc**
(<https://github.com/lboasso/oberonc>, MIT, Copyright (c) 2017 Luca Boasso).
Each source file repeats the full MIT notice at the top.  Only mechanical
changes were made for GPCP/Component Pascal: `Console` output, explicit
`BEGIN`, `EXTENSIBLE` on record bases, and temporary variables where the
current backend traps on `a[i](...)` (`liveActuals`) or `VAR` procedure
parameters (`TypeOfBox`).

| Case | Origin | What is checked |
|---|---|---|
| `proceq_ref_oberonc` | `ProcComparisons.Mod` | the Oberon reference assertions `P2 = P1`, `P2 = P2`, `P2 # NIL`, `P2 = NIL` (expected `1 2 3`) |
| `procvars_ref_basic` | `ProcVariables0.Mod` | procedure values in globals/locals, records, pointers and value parameters |
| `procvars_ref_arrays` | `ProcVariables1.Mod` | arrays of procedure values and calls in a loop |
| `procvars_ref_fields` | `ProcVariables3.Mod` | procedure-typed record field, array element and parameter |
| `procvars_ref_ptype` | `ProcType.Mod` | a named procedure type as a value parameter |
| `procvars_ref_nil` | `ProcVariables7.Mod` | `NIL` assignment, calls, `NIL` as a value argument |
| `procsig_ref_equal` | `TestEqualSignature00.Mod` | anonymous procedure types with equal signatures and open arrays |
| `nested_ref_calls` | `TestNestedProcs.Mod` | nested procedure calls (not yet nested procedure *values*) |

Licensed but not imported as-is: `ProcVariables2.Mod` (record extension plus a
`VAR` procedure parameter), `ProcVariables4.Mod` (procedure `VAR` parameter of a
function), `ProcVariables5.Mod` (anonymous-to-named procedure type assignment)
are blocked by the separate backend gaps listed below.  `ProcVariables6.Mod`
(nested procedure escaping through a `VAR` parameter) is the stage-2 baseline
and will be imported with the nested-procedure work.

Sources considered but not used: OfrontPlus (BSD-2-Clause) has no
procedure-value tests (`Mod/Test` covers `SYSTEM`/files/console only);
Mob/MultiOberon (`Omtest/Mod/Omc*_test.odc`) is LGPLv3 and uses BlackBox `.odc`
documents — reference only.

## Nested procedure values (stage 2)

These cases define the target semantics for nested procedure values: the
captured activation record (XHR / static link) is part of the value's
identity.  They are the TDD baseline for the nested-procedure work and are
expected to **fail** (currently the compiler aborts in code generation)
until that change lands.

| Case | What is checked |
|---|---|
| `nested_capture` | a nested value captures enclosing locals, is callable after the enclosing procedure returns, and two values from one activation compare equal |
| `nested_activations` | values of the same nested procedure from different activations compare unequal; calls see their own captured state |
| `nested_nocapture` | a nested value with an empty environment is equal to another value of the same procedure and stays callable |
| `nested_ref_escape` | `ProcVariables6.Mod` from oberonc (MIT): nested procedure escapes through a `VAR` parameter |

## Not covered

* **Call through an array element.**  `a[i](x)` where `a` is an array of
  procedure values traps in `ExprDesc.liveActuals` with
  `WITH else-trap: type = ExprDesc_BinaryX`.  The imported
  `procvars_ref_arrays` case stores the element in a temporary first.
* **`VAR` procedure parameter of a function.**  A function with a
  `VAR`/`OUT` procedure-typed parameter (for example
  `PROCEDURE F(VAR p: P): INTEGER`) traps in `JavaUtil.TypeOfBox` with
  `TypeOfBox of non-base type`.  Proper procedures with `VAR` procedure
  parameters (as in `proceq_fields_params`) work.
* **Anonymous procedure type assigned to a named one.**  Assigning a value
  received through an anonymous `PROCEDURE (...)` parameter to a variable of a
  named procedure type emits a `putstatic` with incompatible types and fails
  class verification.  This blocks `ProcVariables5.Mod`.
* **Named exported procedure type + imported procedure literal.**  In the
  current backend `f := ImportedProc` where the type is a named exported
  `PROCEDURE` type emits a bad method descriptor (the call gets the anonymous
  proc type as its result type), producing
  `ClassFormatError: Field ... has illegal signature`.  This is independent of
  equality, so `proceq_cross` uses exported getters instead of imported
  literals; it needs its own fix and test.
* **ADR-015 (super call to an implement-only method).**  The parser gate is
  ported, but the existing semantic check in `CheckSuper` rejects the call with
  error 118 for any concrete method in this GPCP revision (the `extns` mask
  test), so there is no program that would pass on the patched compiler.
* **ADR-040 (nested `WITH`).**  The parser accepts the nested form after the
  patch, but code generation currently crashes in `JavaMaker.WithTest` with a
  `LocId`/`VarId` cast error.  A regression test would fail for reasons outside
  this patch set.
* **ADR-050 with a missing weak `.cps`.**  The “missing file is not an error”
  branch is implemented but not automated, because the generated class then
  refers to a type that was never read and the runtime call fails with
  `NoSuchMethodError`; the useful part (recursive reads) is covered by
  `adr050_indirect_import`.
