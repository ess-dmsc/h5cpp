#!/bin/bash
filename="$1"
DEL="-->"
searchpath="$2"

infiles=$(find $searchpath -type f)

function sedeasy {
  sed -i "s/$(echo $1 | sed -e 's/\([[\/.*]\|\]\)/\\&/g')/$(echo $2 | sed -e 's/[\/&]/\\&/g')/g" $3
}

while read -r line
do
    from=$(echo $line | awk -v delimeter="$DEL" '{split($0,a,delimeter)} END{print a[1]}')
    to=$(echo $line | awk -v delimeter="$DEL" '{split($0,a,delimeter)} END{print a[2]}')

    echo "Replacing"
    echo "  from: $from"
    echo "  to: $to"

    for i in $infiles
    do
      echo "  File:  $i"
      sedeasy "$from" "$to" $i
    done

done < "$filename"
