#!/usr/bin/env bash
set -euo pipefail
size=2571.11

echo "scale=18 ; $1 / $size" | bc
