#!/usr/bin/env bash
set -euo pipefail
size=2571.11

met=$(echo "scale=18 ; $1 / $size" | bc)
echo $met | xclip -selection clipboard
echo $met | dmenu
#notify-send $met
