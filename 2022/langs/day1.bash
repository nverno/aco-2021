#!/usr/bin/env bash

declare -a elves
i=0
cur=0
while read -r line; do
    if [ -z "$line" ]; then
        (( i++ ))
        elves+=($(printf "%05d" $cur))
        cur=0
    else
        cur=$(expr "$line" + "$cur")
    fi
done

IFS=$'\n' sorted=($(sort <<< "${elves[*]}"))
unset IFS

n=${#sorted[@]}
echo Part 1: "${sorted[$len-1]}"

top=0
for i in $(seq $(( n - 3 )) $(( n - 1 ))); do
    top=$(expr "$top" + "${sorted[$i]}")
done
echo Part 2: "$top"
