#!/bin/bash

SOURCE_PATH=$1

OUTPUT_DIR=$PWD/
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

LISTS_PATH=$DIR/functions/*

tot_found=0
tot_not_found=0

for filename in ${LISTS_PATH}; do
  basename=$(basename $filename)
  outfile=${OUTPUT_DIR}/${basename}
  found=0
  not_found=0

  echo "" > $outfile

  while read line; do
    if grep -qr "$line" ${SOURCE_PATH}; then
      ((found++))
    else
      echo "$line" >> $outfile
      ((not_found++))
    fi
  done <<< "$(cat ${filename})"

  ((total=found+not_found))
  ((tot_found=tot_found+found))
  ((tot_not_found=tot_not_found+not_found))

  percent=$(awk "BEGIN { pc=100*${found}/${total}; i=int(pc); print (pc-i<0.5)?i:i+1 }")

  text=$(printf '%s:\t %s\t / %s\t = %s\n' "$basename" "$found" "$total" "$percent%" | expand -t 7)

  echo "" >> $outfile
  echo "${text}" >> $outfile


  echo "${text}"
done

((tot_total=tot_found+tot_not_found))
percent=$(awk "BEGIN { pc=100*${tot_found}/${tot_total}; i=int(pc); print (pc-i<0.5)?i:i+1 }")
text=$(printf '%s:\t %s\t / %s\t = %s\n' "TOTAL" "$tot_found" "$tot_total" "$percent%" | expand -t 7)
echo "${text}"
