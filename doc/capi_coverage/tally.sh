#!/bin/bash

SOURCE_PATH=$1
RST_PATH=$2

OUTPUT_DIR=$PWD/
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

LISTS_PATH=$DIR/functions/*

tot_found=0
tot_not_found=0

rstfile=${RST_PATH}/capi.rst

text=$(printf '===============\nC API Coverage\n===============\n')
echo "${text}" > $rstfile

text=$(printf '\n')
echo "${text}" >> $rstfile

text=$(printf '.. csv-table:: Wrapped C API functions\n   :header: "API", "wrapped", "total", "percent"\n   :widths: 20, 20, 20, 20\n')
echo "${text}" >> $rstfile

text=$(printf '\n')
echo "${text}" >> $rstfile

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

  text=$(printf '   "%s", "%s", "%s", "%s"\n' "$basename" "$found" "$total" "$percent%" | expand -t 7)

  echo "" >> $outfile
  echo "${text}" >> $outfile
  echo "${text}" >> $rstfile

done

((tot_total=tot_found+tot_not_found))
percent=$(awk "BEGIN { pc=100*${tot_found}/${tot_total}; i=int(pc); print (pc-i<0.5)?i:i+1 }")
text=$(printf '   "%s", "%s", "%s", "%s"\n' "Total" "$tot_found" "$tot_total" "$percent%" | expand -t 7)

echo "${text}" >> $rstfile

