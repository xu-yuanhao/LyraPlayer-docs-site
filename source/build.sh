#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
public=$(mktemp -d)
trap 'rm -rf "$public"' EXIT
cp -a ../{downloads,licenses,thanks,logo.svg,signature.svg,vp-icons.css,.nojekyll} "$public/"
LYRA_DOCS_PUBLIC_DIR="$public" ./node_modules/.bin/vitepress build --outDir dist
