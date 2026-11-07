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
| `compile-error.txt` | expected compiler diagnostic substring; at least one module must fail with it and nothing is executed |
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

## CP conformance regressions

| Case | What is checked |
|---|---|
| `array_proc_call` | direct calls through array elements of procedure type (global, local and open-array `ARRAY OF` parameters) |
| `var_proc_param_function` | functions with `VAR`/`OUT` procedure parameters (explicit result uses the return slot, so parameters are boxed) |

## fixProcEqual (procedure values on the JVM)

These cases define the target semantics for procedure-value equality: a value
is identified by owner + name + signature.  This branch follows strict
Component Pascal, so methods and procedures local to another procedure are not
procedure values (see the strict-CP section below).  The full extension variant
(nested and method values) lives on the `fixProcEqualExt` branch.

| Case | What is checked |
|---|---|
| `proceq_basic` | `=` / `#` on procedure values, `NIL`, literal-vs-literal, literal-vs-variable, calls through values |
| `proceq_fields_params` | values in record fields, arrays, value and `VAR` parameters |
| `proceq_cross` | values produced in one module compared in another; same name/signature but a different owner stays unequal |
| `proceq_named_types` | equal procedure types denoted by different type identifiers compare equal (CP report, Appendix A) |
| `proceq_special_abi` | named types in a `-special` interface keep `CP/<Mod>/<Mod>_<Type>`; two identical signatures stay distinct; wrappers implement `CP.CPJrts.ProcKey` across the native Java ABI |
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
| `procvars_ref_arrays` | `ProcVariables1.Mod` | arrays of procedure values, direct `a[i](...)` calls in a loop |
| `procvars_ref_fields` | `ProcVariables3.Mod` | procedure-typed record field, direct array-element call, parameter |
| `procvars_ref_ptype` | `ProcType.Mod` | a named procedure type as a value parameter |
| `procvars_ref_nil` | `ProcVariables7.Mod` | `NIL` assignment, calls, `NIL` as a value argument |
| `procvars_ref_recursive` | `ProcVariables5.Mod` | recursive passing of procedure values through anonymous and named types |
| `procvars_ref_varparams` | `ProcVariables4.Mod` | procedure types with `VAR` parameters, including `VAR` procedure parameters |
| `procsig_ref_equal` | `TestEqualSignature00.Mod` | anonymous procedure types with equal signatures and open arrays |
| `nested_ref_calls` | `TestNestedProcs.Mod` | nested procedure calls only (procedure values are forbidden in strict CP) |

Licensed but not imported as-is: `ProcVariables2.Mod` uses Oberon-07 record
extension/assignment that Component Pascal rejects (the base would need
`EXTENSIBLE`, and extension-to-base assignment is illegal).  `ProcVariables6.Mod`
(nested procedure escaping through a `VAR` parameter) is not imported because
strict CP rejects local procedures as procedure values (error 165).

Sources considered but not used: OfrontPlus (BSD-2-Clause) has no
procedure-value tests (`Mod/Test` covers `SYSTEM`/files/console only);
Mob/MultiOberon (`Omtest/Mod/Omc*_test.odc`) is LGPLv3 and uses BlackBox `.odc`
documents — reference only.

## General oberonc tests (MIT)

These are the remaining standalone oberonc tests that compile and run after
mechanical adaptation (Console output helpers, explicit `BEGIN`, `CPmain`
import).  Each file carries the MIT notice.

```
oberonc_CaseNum0, CaseNum1, CommutativeSwap, ConstantFoldingAndLoadOp,
ForwardPointerRef, OpenArrays, OpenArrays2, Out0, Out1, Out4, Out5, Out6,
RecordAssignment2, RecordParam, Strings2, TestAnonymousName, TestAssert,
TestCPS, TestFor, TestFor1, TestFunction0, TestINC1, TestINCLAndEXCL,
TestReturn0, UniqueTypeAndProcNames, UTF8String
```

Not imported from this suite:

- tests whose expected output uses `WriteReal` (a CP formatting helper and
  exact real-number alignment would be needed);
- Oberon-07-only builtins (`ASR`/`LSL`/`ROR`/`AND`/`BOR`, `ReadInt` in the
  sample programs), and `WHILE ... ELSIF` syntax (`Out3`);
- CP type-system differences: record extension without `EXTENSIBLE`,
  open-array variables, whole-open-array assignment, `BYTE` formals, and
  name-equivalence of array types;
- multi-module import suites (`TestImport*`, `TestTypeGuardExt`,
  `TestStringsMod`) which need auxiliary modules and explicit compile order;
- tests that currently expose unrelated backend defects (`Out2`, `TestODD`,
  `CaseChar0`) or Oberon-07 arithmetic/overflow semantics (`DivMul`,
  `TestINC0`).

## Strict CP: forbidden procedure values

Component Pascal (report Ch. 6.5) allows a procedure value only for a named,
non-local procedure: methods and procedures local to another procedure are
explicitly excluded.  These cases must fail to compile with error 165
(`This procedure cannot be used as a procedure value`):

| Case | What is checked |
|---|---|
| `strict_nested_assign` | `f := Inner` for a local procedure |
| `strict_nested_param` | a local procedure passed to a procedure-typed formal |
| `strict_nested_compare` | a local procedure in a `=`/`#` comparison |
| `strict_nested_return` | a local procedure returned as a procedure value |
| `strict_nested_array` | a local procedure assigned to a procedure-typed array element |
| `strict_method_value` | a bound method (`f := t.Add`) |
| `strict_method_field` | a bound method assigned to a procedure-typed record field |

## Imported procedure literals (stage 3)

| Case | What is checked |
|---|---|
| `import_literal_named_type` | `f := Lib.Proc` with a named exported `PROCEDURE` type: correct JVM descriptor, calls, equality with a library-produced value, imported literals on both sides, and an anonymous-vs-named comparison |

The original defect was a bogus call descriptor
(`Field ... has illegal signature`, `ClassFormatError`) when a named exported
procedure type was combined with an imported procedure literal.  The
procedure-type host-class work in stage 1 removed it, so this case is the
regression guard rather than a separate code change.  It was verified to fail
with the stock `jars/gpcp.jar` (illegal signature) and on the stage-1 compiler
(anonymous-vs-named comparison).

## Not covered

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
