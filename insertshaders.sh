#!/usr/bin/sh

IFS="\n"
path="pn/src/pn_default_shaders.h"

ReadFile() {
    echo "$(cat $1)" | sed -E ':a;N;$!ba;s/\r{0,1}\n/\\n/g' 
}

InsertShader() {
    text=$(ReadFile $1)
    echo "const char $2[] = \"$text\";" >> "$path"
}

Init() {
    > "$path" # Clear the file.
    echo "#pragma once" >> "$path"
}

Init

InsertShader res/shaded.vs __pn_shaded_vert
InsertShader res/shaded.fs __pn_shaded_frag
