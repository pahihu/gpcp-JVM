# bbcb-fe-compiler
Hacked Gardens Point Component Pascal compiler for the BlackBox Component Builder Frankenstein Edition (JVM)

## Tests

Regression tests for the ported compiler patches (commit `f4966be`) live in
`tests/gpcp/`.  The runner rebuilds the compiler from `sources/gpcp` and then
compiles and executes the Component Pascal test cases:

```bash
tests/gpcp/run-tests.sh
```

See `tests/gpcp/README.md` for the case format and the ADR coverage table.

Gardens Point Component Pascal (https://github.com/k-john-gough/gpcp) original license: gpcpLICENSE.md

gpcp-JVM (https://github.com/pahihu/gpcp-JVM) license (same): pahihuLICENSE.md

bbcb-fe-compiler license (same): LICENSE.md
