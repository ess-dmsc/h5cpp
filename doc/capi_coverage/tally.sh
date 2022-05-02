#!/bin/bash

SOURCE_PATH=$1
RST_PATH=$2

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

LISTS_PATH=$DIR/functions/*

tot_found=0
tot_not_found=0
toctree=""

rstfile=${RST_PATH}/index.rst

echo "==================" > $rstfile
echo "C API Usage" >> $rstfile
# echo "C API Coverage" >> $rstfile
echo "==================" >> $rstfile
echo "" >> $rstfile
echo ".. csv-table:: Wrapped C API functions" >> $rstfile
echo '   :header: "API", "wrapped", "total", "percent"' >> $rstfile
echo "   :widths: 20, 20, 20, 20" >> $rstfile
echo "" >> $rstfile

for filename in ${LISTS_PATH}; do
  basename=$(basename $filename)
  outfile=${RST_PATH}/${basename}.rst
  found=0
  not_found=0
  toctree="${toctree}
   ${basename}"
  echo ".. _capi-${basename}:" > $outfile
  echo "" >> $outfile
  echo "===================================" >> $outfile
#  echo "Wrapper coverage of ${basename} functions" >> $outfile
  echo "Usage of ${basename} functions" >> $outfile
  echo "===================================" >> $outfile
  echo "" >> $outfile

  while read line; do
    if grep -qr "$line" ${SOURCE_PATH}; then
      echo -e "* **$line**\n" >> $outfile
      ((found++))
    else
      echo -e "* $line\n" >> $outfile
      ((not_found++))
    fi
  done <<< "$(cat ${filename})"

  ((total=found+not_found))
  ((tot_found=tot_found+found))
  ((tot_not_found=tot_not_found+not_found))

  percent=$(awk "BEGIN { pc=100*${found}/${total}; i=int(pc); print (pc-i<0.5)?i:i+1 }")

  text=$(printf '   ":ref:`%s <capi-%s>`", "%s", "%s", "%s"\n' "$basename" "$basename" "$found" "$total" "$percent%" | expand -t 7)

  echo "" >> $outfile
  echo "${text}" >> $rstfile

done

((tot_total=tot_found+tot_not_found))
percent=$(awk "BEGIN { pc=100*${tot_found}/${tot_total}; i=int(pc); print (pc-i<0.5)?i:i+1 }")
text=$(printf '   "%s", "%s", "%s", "%s"\n' "Total" "$tot_found" "$tot_total" "$percent%" | expand -t 7)

echo "${text}" >> $rstfile
echo "" >> $rstfile
echo ".. toctree::" >> $rstfile
echo "   :hidden:" >> $rstfile
echo "   :maxdepth: 1">> $rstfile
echo "${toctree}" >> $rstfile
