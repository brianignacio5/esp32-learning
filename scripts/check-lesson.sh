#!/usr/bin/env bash
# Run one lesson, or every lesson, without modifying the working tree.
# Host tests use the ESP-IDF linux target. Wokwi runs only with --wokwi
# and only when WOKWI_CLI_TOKEN is set.
#
# Usage: scripts/check-lesson.sh <lesson-number|all> [--solution] [--wokwi]

set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

SOLUTION=0
WOKWI=0
TARGET=""

usage() {
  echo "Usage: scripts/check-lesson.sh <lesson-number|all> [--solution] [--wokwi]" >&2
  exit 2
}

for arg in "$@"; do
  case "$arg" in
    --solution) SOLUTION=1 ;;
    --wokwi) WOKWI=1 ;;
    -h|--help) usage ;;
    *)
      if [[ -n "$TARGET" ]]; then
        usage
      fi
      TARGET="$arg"
      ;;
  esac
done

if [[ -z "$TARGET" ]]; then
  usage
fi

pad_num() {
  local n="$1"
  if [[ "$n" =~ ^[0-9]$ ]]; then
    printf '0%s\n' "$n"
  else
    printf '%s\n' "$n"
  fi
}

lesson_path() {
  local n match dir
  n="$(pad_num "$1")"
  match=""
  for dir in "$ROOT/lessons/${n}-"*; do
    if [[ -d "$dir" ]]; then
      match="$dir"
      break
    fi
  done
  if [[ -z "$match" ]]; then
    echo "No lesson numbered ${n}" >&2
    return 1
  fi
  printf '%s\n' "$match"
}

apply_solution() {
  local root="$1"
  local src base
  shopt -s nullglob
  for src in "$root/logic/solution/"*.c; do
    base="$(basename "$src")"
    cp "$src" "$root/logic/$base"
    echo "Applied logic/${base}"
  done
  for src in "$root/firmware/main/solution/"*.c; do
    base="$(basename "$src")"
    cp "$src" "$root/firmware/main/$base"
    echo "Applied firmware/main/${base}"
  done
  shopt -u nullglob
}

run_host() {
  local root="$1"
  local elf
  if [[ ! -f "$root/host_test/CMakeLists.txt" ]]; then
    echo "No host test."
    return 0
  fi
  if [[ -z "${IDF_PATH:-}" ]]; then
    echo "IDF_PATH is not set. Source the ESP-IDF export script, then retry." >&2
    return 1
  fi
  (
    cd "$root/host_test"
    idf.py --preview set-target linux
    idf.py build
    elf=""
    for candidate in build/*.elf; do
      if [[ -f "$candidate" ]]; then
        elf="$candidate"
        break
      fi
    done
    if [[ -z "$elf" ]]; then
      echo "Host test ELF was not produced." >&2
      return 1
    fi
    "./${elf}"
  )
}

run_wokwi() {
  local root="$1"
  if [[ ! -f "$root/firmware/scenario.yaml" ]]; then
    echo "No Wokwi scenario."
    return 0
  fi
  if [[ -z "${WOKWI_CLI_TOKEN:-}" ]]; then
    echo "WOKWI_CLI_TOKEN is not set; skipping the simulator."
    return 0
  fi
  if [[ -z "${IDF_PATH:-}" ]]; then
    echo "IDF_PATH is not set. Source the ESP-IDF export script, then retry." >&2
    return 1
  fi
  if ! command -v wokwi-cli >/dev/null 2>&1; then
    echo "wokwi-cli is not on PATH." >&2
    return 1
  fi
  (
    cd "$root/firmware"
    idf.py set-target esp32
    idf.py build
    wokwi-cli . --scenario scenario.yaml --timeout 120000
  )
}

run_one() {
  local num="$1"
  local src name tmp status
  src="$(lesson_path "$num")"
  name="$(basename "$src")"
  echo "===== ${name} ====="
  tmp="$(mktemp -d "${TMPDIR:-/tmp}/lesson-${name}.XXXXXX")"
  cp -a "${src}/." "${tmp}/"
  if [[ "$SOLUTION" -eq 1 ]]; then
    apply_solution "$tmp"
  fi
  status=0
  run_host "$tmp" || status=$?
  if [[ "$status" -eq 0 && "$WOKWI" -eq 1 ]]; then
    run_wokwi "$tmp" || status=$?
  fi
  rm -rf "$tmp"
  return "$status"
}

if [[ "$TARGET" == "all" ]]; then
  found=0
  for dir in "$ROOT/lessons/"[0-9][0-9]-*; do
    if [[ ! -d "$dir" ]]; then
      continue
    fi
    found=1
    num="$(basename "$dir")"
    num="${num%%-*}"
    run_one "$num"
  done
  if [[ "$found" -eq 0 ]]; then
    echo "No lessons found." >&2
    exit 1
  fi
else
  run_one "$TARGET"
fi
