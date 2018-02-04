file=${1}
new_text=${2}
lineNum="$(grep -n "<source>" ${file} | head -n 1 | cut -d: -f1)"
theLine="'${lineNum}s/.*/<source>${new_text}<\/source>/'"
command="sed -i ${theLine} ${file}"
eval $command
