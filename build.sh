shPath="$(realpath $0)"
shDir="$(dirname $shPath)"
shName="$(basename $shPath)"

target=$1

srcDir="$shDir/src"
binDir="$shDir/bin"
makDir="$shDir/mak"

ord() {
    LC_CTYPE=C printf '%d' "'$1"
}
getLines() {
    local name=$1
    local path=$2
    eval "$name=()"
    local state=0
    local line=
    local char=
    local code=
    while IFS= read -n 1 char; do
        code="$(ord "$char")"
        #Newline
        if [ $state = 0 ]; then
            #Check if comment
            if [ "$char" = "#" ]; then
                state=2
            #Check if end of new line
            elif [ ! "$code" -lt "32" ]; then
                state=1
                line="$char"
            fi
        #Content
        elif [ $state = 1 ]; then
            #Check if comment
            if [ "$char" = "#" ]; then
                state=2
            #Check if start of new line
            elif [ "$code" -lt "32" ]; then
                state=0
            fi
            #Check if state changed
            if [ ! $state = 1 ]; then
                eval "$name+=(\"$line\")"
            else
                line+="$char"
            fi
        #Comment
        else
            #Check if start of new line
            if [ "$code" -lt "32" ]; then
                state=0
            fi
        fi
    done < "$path"
    #Check if content
    if [ $state = 1 ]; then
        eval "$name+=(\"$line\")"
    fi
}

#Get OS info
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    os_ext_app=""
    os_ext_lib=".so"
elif [[ "$OSTYPE" == "msys" ]]; then
    os_ext_app=".exe"
    os_ext_lib=".dll"
else
    echo "ERROR: $OSTYPE is not supported." >&2;
    exit 1
fi

#Get libraries
getLines libs "$shDir/libs"
libs_dir=()
for lib in "${libs[@]}"; do
    libs_dir+=("$shDir/src/$lib")
done

#Clean if cleaning
if [ "$target" = "clean" ]; then
    echo "Clean"
    for lib_dir in "${libs_dir[@]}"; do
        rm -fr "$lib_dir/object"
    done
    rm -fr "$binDir"
    rm -fr "$makDir"
    exit 
fi

#Error if not building
if [ ! -z "$target" ]; then
    echo "ERROR: The target $target is not supported." >&2;
    exit 1
fi

#Build
mkdir -p "$makDir"
#Make
makMake="$makDir/make"
if [ ! -f "$makMake" ]; then
    echo "BINDIR := $binDir" >>"$makMake"
    echo "MAKDIR := $makDir" >>"$makMake"
    echo "LIB_NAME := \$(notdir \$(CURDIR))" >>"$makMake"
    echo "LIB_SAVEDIR := \$(BINDIR)/\$(LIB_NAME)" >>"$makMake"
    echo "LIB_SAVEPATH := \$(LIB_SAVEDIR)/\$(LIB_NAME)$os_ext_lib" >>"$makMake"
    #Src directories
    echo "LIB_SRC_SOURCEDIR := \$(CURDIR)/source" >>"$makMake"
    echo "LIB_SRC_HEADERDIR := \$(CURDIR)/header" >>"$makMake"
    echo "LIB_SRC_OBJECTDIR := \$(CURDIR)/object" >>"$makMake"
    #Src files
    echo "LIB_SRC_SOURCES := \$(wildcard \$(LIB_SRC_SOURCEDIR)/*.cpp)" >>"$makMake"
    echo "LIB_SRC_OBJECTS := \$(foreach source,\$(notdir \$(LIB_SRC_SOURCES)),\$(LIB_SRC_OBJECTDIR)/\$(source:.cpp=.o))" >>"$makMake"
    #Deps
    echo "LIB_DEPS := \$(shell bash \$(MAKDIR)/\$(LIB_NAME).deps.sh)" >>"$makMake"
    #Recipes
    echo "CC := g++" >>"$makMake"
    echo "CFLAGS := -Wall -Wno-unknown-pragmas -g" >>"$makMake"
    #Library recipe
    echo "\$(LIB_SAVEPATH): \$(LIB_SRC_OBJECTS)" >>"$makMake"
    echo -n -e "\t" >>"$makMake"
    echo "@echo \$(notdir \$(LIB_SAVEPATH))" >>"$makMake"
    echo -n -e "\t" >>"$makMake"
    echo "@mkdir -p \$(shell dirname \$(LIB_SAVEPATH))" >>"$makMake"
    echo -n -e "\t" >>"$makMake"
    echo -n "@\$(CC) \$(CFLAGS) " >>"$makMake"
    echo -n "-fpic -shared " >>"$makMake"
    echo -n "-L\$(BINDIR) " >>"$makMake"
	echo -n "\$(foreach dep,\$(LIB_DEPS),-l:\$(dep)/\$(dep)$os_ext_lib) " >>"$makMake"
    echo -n "-o \$(LIB_SAVEPATH) " >>"$makMake"
    echo "\$(LIB_SRC_OBJECTS)" >>"$makMake"
    #Object recipe
    echo "\$(LIB_SRC_OBJECTDIR)/%.o: \$(LIB_SRC_SOURCEDIR)/%.cpp" >>"$makMake"
    echo -n -e "\t" >>"$makMake"
    echo "@echo \$(notdir \$@)" >>"$makMake"
    echo -n -e "\t" >>"$makMake"
    echo "@mkdir -p \$(shell dirname \$@)" >>"$makMake"
    echo -n -e "\t" >>"$makMake"
    echo -n "@\$(CC) \$(CFLAGS) " >>"$makMake"
    echo -n "-c " >>"$makMake"
    echo -n "-I\$(LIB_SRC_HEADERDIR) " >>"$makMake"
	echo -n "\$(foreach dep,\$(LIB_DEPS),-I\$(BINDIR)/\$(dep)) " >>"$makMake"
    echo -n "-o\$@ " >>"$makMake"
    echo "\$<" >>"$makMake"
fi
#Loop
for i in "${!libs[@]}"; do
    lib="${libs[$i]}"
    lib_dir="${libs_dir[$i]}"
    echo "Bulding $lib"
    #Bin
    lib_bin="$binDir/$lib"
    mkdir -p "$lib_bin"
    #Deps
    lib_src_deps="$lib_dir/deps"
    lib_bin_deps="$lib_bin/deps"
    lib_depsDest="$makDir/$lib.deps.sh"
    rm -fr "$lib_bin_deps" "$lib_depsDest"
    if [ -f "$lib_src_deps" ]; then
        getLines lib_deps "$lib_src_deps"
        for lib_dep in ${lib_deps[@]}; do
            echo "$lib_dep" >>"$lib_bin_deps"
            echo "echo \"$lib_dep\"" >>"$lib_depsDest"
        done
    else
        echo "" >>"$lib_bin_deps"
        echo "echo \"\"" >>"$lib_depsDest"
    fi
    #Headers
    cp -u $lib_dir/header/*.h "$lib_bin"
    #Make
    make --no-print-directory -C "$lib_dir" -f "$makMake"
done