path=$1
tarfile=$2
bName=$(basename -- "$path")
zipFolderRoot=$(echo $tarfile | rev | cut -f 2- -d '.' | rev)
zipFolderRootBName=$(basename -- "$zipFolderRoot")

if [ -e "$zipFolderRoot" ] && [ "$bName" != "$zipFolderRootBName" ]; then
    mv $zipFolderRoot $path
fi
