#!/usr/bin/env bash
set -euo pipefail
sdk_root=$(cd -- "$(dirname -- "$0")/.." && pwd)
: "${ANDROID_NDK_HOME:?Set ANDROID_NDK_HOME to your Android NDK directory}"
case "$(uname -s)" in
    Linux) host=linux-x86_64 ;;
    Darwin) host=darwin-x86_64 ;;
    *) echo 'Use the Android NDK from a Linux or macOS shell.' >&2; exit 1 ;;
esac
cc="$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/$host/bin/aarch64-linux-android26-clang"
mkdir -p "$sdk_root/out"
stage=$(mktemp -d)
trap 'rm -rf "$stage"' EXIT
for spec in root:frame style:style rules:playback-rules; do
    example=${spec%:*}
    kind=${spec#*:}
    "$cc" -std=c11 -Oz -fPIC -fvisibility=hidden -shared -I "$sdk_root/include" \
        "$sdk_root/examples/$example.c" -o "$stage/plugin.so"
    printf 'id = "example.%s"\nversion = "1.0"\nabi = 3\ntype = "%s"\nentry = "plugin.so"\n' \
        "$example" "$kind" > "$stage/manifest.toml"
    python3 -m zipfile -c "$sdk_root/out/example.$example.zip" "$stage/manifest.toml" "$stage/plugin.so"
done
