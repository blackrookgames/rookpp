shPath="$(realpath $0)"
shDir="$(dirname $shPath)"

target=$1

#Remove temp if it already exists
tempPath="$shPath.temp"
rm -fr "$tempPath"

#Get paths
getpaths() {
    local dir=$1
    local ext=$2
    local paths=
    mapfile -t paths <<< "$(find "$dir" -type f -name "*$ext.sh")"
    local path=
    for path in "${paths[@]}"; do
        echo -n "${path%.sh} "
    done
}
autopaths=""
autopaths+="$(getpaths "$shDir" ".h")"
autopaths+="$(getpaths "$shDir" ".cpp")"

#Clean if cleaning
if [ "$target" = "clean" ]; then
    echo "Clean"
    rm -fr $autopaths
    exit 
fi

#Error if not building
if [ ! -z "$target" ]; then
    echo "ERROR: The target $target is not supported." >&2;
    exit 1
fi

#Create temp
autorun() {
    local ext=$1
    echo "%$ext: %$ext.sh"
    echo "	\$(call autorun)"
}
echo "define autorun" >>"$tempPath"
echo "	@echo \$(notdir \$@)" >>"$tempPath"
echo "	@error=\$\$(bash \$< \$@ 2>&1 > /dev/null); \\" >>"$tempPath"
echo "	if [ -n \"\$\$error\" ]; then \\" >>"$tempPath"
echo "		echo \"\$\$error\"; \\" >>"$tempPath"
echo "		rm -fr \$@; \\" >>"$tempPath"
echo "	fi" >>"$tempPath"
echo "endef" >>"$tempPath"
autorun ".h" >>"$tempPath"
autorun ".cpp" >>"$tempPath"

#Make
make --no-print-directory -f "$tempPath" $autopaths

#Remove temp
rm -fr "$tempPath"