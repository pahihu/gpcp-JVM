#!/usr/bin/env bash
#
# Regression tests for the compiler patches ported from bbcb-fe in f4966be.
#
# The tests are Component Pascal modules.  The script first rebuilds the
# compiler from sources/gpcp with the bootstrap jars/gpcp.jar, then compiles
# every case with the freshly built compiler.  Cases with expected.txt are
# executed as CP.<Module>.<Module> and their stdout is compared byte for byte.
#
# Usage:
#   tests/gpcp/run-tests.sh                 # run everything
#   tests/gpcp/run-tests.sh adr012 adr047   # run cases whose name matches
#   KEEP=1 tests/gpcp/run-tests.sh          # keep the temporary build tree
#
set -u

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
CASE_ROOT="$ROOT/tests/gpcp/cases"
JAVA=${JAVA:-java}
JARS="$ROOT/jars"
CPSYM=".:$ROOT/symfiles:$ROOT/symfiles/JvmSystem"
STAGE=${STAGE:-${TMPDIR:-/tmp}/gpcp-tests.$$}
KEEP=${KEEP:-0}
COMPILER_CP="$STAGE/compiler:$JARS/gpcp.jar:$JARS/asm-5.1.jar:$JARS/cprts.jar"

filters=()
while [ $# -gt 0 ]; do
  case "$1" in
    --keep) KEEP=1 ;;
    -h|--help)
      sed -n '2,13p' "$0" | sed 's/^# \{0,1\}//'
      exit 0 ;;
    *) filters+=("$1") ;;
  esac
  shift
done

cleanup() {
  if [ "$KEEP" = 1 ]; then
    echo "kept temporary tree: $STAGE"
  else
    rm -rf "$STAGE"
  fi
}
trap cleanup EXIT

mkdir -p "$STAGE/cases"

build_compiler() {
  local log="$STAGE/compiler-build.log" src="$STAGE/gpcp-src"
  echo "==> building compiler from sources/gpcp"
  # Build in a copy: CPMake writes *.cps next to the sources, and the tests
  # must not dirty the working tree.
  rm -rf "$src"
  cp -a "$ROOT/sources/gpcp" "$src"
  if ! ( cd "$src" &&
         CPSYM="$CPSYM" "$JAVA" -jar "$JARS/cpmake.jar" \
           -all -nowarn -asm8 -clsdir:"$STAGE/compiler" gpcp ) >"$log" 2>&1; then
    echo "compiler build failed:" >&2
    cat "$log" >&2
    return 1
  fi
  echo "    ok"
}

is_special() {
  local m=$1 s
  shift
  for s in "$@"; do
    [ "$s" = "$m" ] && return 0
  done
  return 1
}

run_case() {
  local src=$1
  local name work m log actual runmod s
  local expected_err="" compile_failed=0
  local -a mods=() specials=() flags=()

  name=$(basename "$src")
  work="$STAGE/cases/$name"
  mkdir -p "$work"
  cp -a "$src/." "$work/"

  if [ -f "$work/compile-error.txt" ]; then
    expected_err=$(cat "$work/compile-error.txt")
  fi

  if [ -f "$work/prepare.py" ]; then
    if ! ( cd "$work" && python3 prepare.py ); then
      echo "  prepare failed"
      return 1
    fi
  fi

  if [ -f "$work/modules.txt" ]; then
    mapfile -t mods < "$work/modules.txt"
  else
    mapfile -t mods < <(cd "$work" && printf '%s\n' *.cp | sort)
  fi
  if [ -f "$work/special.txt" ]; then
    mapfile -t specials < "$work/special.txt"
  fi

  for m in "${mods[@]}"; do
    [ -n "$m" ] || continue
    flags=(-nowarn -list- -asm8 "-symdir:$work" "-clsdir:$work")
    if is_special "$m" "${specials[@]}"; then
      flags+=(-special)
    fi
    log="$work/compile-$m.log"
    if ! ( cd "$work" &&
           CPSYM="$CPSYM" "$JAVA" -cp "$COMPILER_CP" \
             CP.gpcp.gpcp "${flags[@]}" "$m" ) >"$log" 2>&1; then
      if [ -n "$expected_err" ]; then
        if grep -qF -- "$expected_err" "$log"; then
          compile_failed=1
          break
        else
          echo "  compile failed without the expected diagnostic: $m"
          sed 's/^/    /' "$log"
          return 1
        fi
      fi
      echo "  compile failed: $m"
      sed 's/^/    /' "$log"
      return 1
    fi
  done

  if [ -n "$expected_err" ]; then
    if [ "$compile_failed" = 1 ]; then
      return 0
    fi
    echo "  expected compile error was not produced"
    return 1
  fi

  if [ -f "$work/run.txt" ]; then
    runmod=$(head -n1 "$work/run.txt" | tr -d '[:space:]')
    actual="$work/actual.txt"
    if ! ( cd "$work" &&
           "$JAVA" -Dfile.encoding=UTF-8 -cp "$work:$ROOT/libs" \
             "CP.$runmod.$runmod" ) >"$actual" 2>"$work/run.err"; then
      echo "  run failed: CP.$runmod.$runmod"
      sed 's/^/    /' "$work/run.err"
      return 1
    fi
    if [ -f "$work/expected.txt" ]; then
      if ! diff -u "$work/expected.txt" "$actual"; then
        echo "  output mismatch"
        return 1
      fi
    fi
  fi
  return 0
}

build_compiler || exit 1

total=0 passed=0 failed=0 skipped=0
for dir in "$CASE_ROOT"/*/; do
  [ -d "$dir" ] || continue
  name=$(basename "$dir")
  if [ ${#filters[@]} -gt 0 ]; then
    match=0
    for f in "${filters[@]}"; do
      case "$name" in *"$f"*) match=1 ;; esac
    done
    [ "$match" = 1 ] || continue
  fi
  if [ -f "$dir/prepare.py" ] && ! command -v python3 >/dev/null 2>&1; then
    echo "SKIP $name (python3 not found)"
    skipped=$((skipped + 1))
    continue
  fi
  total=$((total + 1))
  if run_case "$dir"; then
    echo "PASS $name"
    passed=$((passed + 1))
  else
    echo "FAIL $name"
    failed=$((failed + 1))
  fi
done

echo
echo "cases: $total, passed: $passed, failed: $failed, skipped: $skipped"
[ "$failed" -eq 0 ]
