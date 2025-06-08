shPath="$(realpath $0)"
shDir="$(dirname $shPath)"
shName="$(basename $0)"
reqArg=$3
if [ -z "$reqArg" ]; then
echo "Use $shName to copy libraries to a certain location"
echo "$shName <libraryName> <dllDir> <hdrDir>"
echo ""
echo "libraryName:   Name of the library to copy"
echo "dllDir:        Directory to copy the *.dll files to"
echo "hdrDir:        Directory to copy the *.h files to"
exit 0
fi

#Get arguments
libraryName="$1"
dllDir="$2"
hdrDir="$3"

#Make sure library exists
libraryDir="$shDir/bin/$libraryName"
if [ ! -d "$libraryDir" ]; then
echo "ERROR: Could not find the library \"$libraryDir\"."
exit 1
fi

#Get dependencies
getDeps() {
    while read -n 1 char; do
        if [ ! -z "${char//[[:space:]]/}" ]; then
            echo -n "$char"
        else
            echo -n " "
        fi
    done < "$1"
}
dependencyFile="$libraryDir/$libraryName.deps.txt"
if [ -f "$dependencyFile" ]; then
    IFS=' ' read -r -a dependencies <<< "$(getDeps "$dependencyFile")"
    IFS=
else
    dependencies=()
fi

#Copy dependencies
for dependency in ${dependencies[@]}; do
    sh "$shPath" "$dependency" "$dllDir" "$hdrDir"
done

#Copy *.dll files
mkdir -p "$dllDir"
cp -u $libraryDir/*.dll "$dllDir"

#Copy *.h files
mkdir -p "$hdrDir"
cp -u $libraryDir/*.h "$hdrDir"