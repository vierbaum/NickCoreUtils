#!/usr/bin/env bash
set -euo pipefail

getDir() {
    echo "123" > ~/log
    f=$(ls)
    dir=$(echo "$f" | dmenu)
    echo $dir
    if [[ -d $dir ]]; then
        cd $dir
        getDir
    elif [[ -f $dir ]]; then
        readFile $dir
        exit 1
    fi
}

readFile () {
    file=$(cat $1)
    file="${file//,/\\n}"
    echo -e "${file//,/\\n}" | dmenu -l 20 | cut -d ":" -f2 | xclip -selection clipboard
}


echo "123" > ~/log
cd /home/nld/Documents/programming/NickCoreUtils
getDir
