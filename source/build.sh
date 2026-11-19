#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
./node_modules/.bin/vitepress build --outDir dist
cp -a ../{downloads,licenses,thanks,logo.svg,signature.svg,vp-icons.css,.nojekyll} dist/
