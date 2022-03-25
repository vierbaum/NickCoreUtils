#!/usr/bin/env bash
set -euo pipefail

sel=$(echo -e "SaarlandCalc\nDatabase" | dmenu -x 6 -y 6 -z 1354 -l 10)
echo $sel
case $sel in
    SaarlandCalc)
        saarlandCalculator.sh $(xclip -o)
        ;;
    Database)
        database.sh
        ;;

esac
