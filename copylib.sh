shPath="$(realpath $0)"
shDir="$(dirname $shPath)"
shName="$(basename $shPath)"

binSrcDir="$shDir/bin"

showHelp() {
    echo -n "bash $shName [--bin <binDir>] [--hdr <hdrDir>] <libname>"
    echo -n -e "\n\n"
    echo "<libName>"
    echo -n "Name of the library to retrieve"
    echo -n -e "\n\n"
    echo "--bin <binDir>"
    echo -n "If specified, the library's binary (as well as the binaries of the libraries "
    echo -n "this library depends on) are copied to <binDir>"
    echo -n -e "\n\n"
    echo "--hdr <hdrDir>"
    echo -n "If specified, the library's header (as well as the headers of the libraries "
    echo -n "this library depends on) are copied to <hdrDir>"
    echo -n -e "\n\n"
}
if [ -z "$1" ]; then
    showHelp
    exit
elif [ "$1" = "--help" ]; then
    showHelp
    exit
fi

getLines() {
    local name=$1
    local path=$2
    local content="$(cat "$path")"
    #Get lines
    local array
    mapfile -t array <<< "$content"
    local item
    local iteml
    local i
    eval "$name=()"
    for item in "${array[@]}"; do
        #Trim comment
        iteml="${#item}"
        i=0
        while [ $i -lt $iteml ]; do
            if [ "${item:$i:1}" = "#" ]; then
                break
            fi
            i="$(expr $i + 1)"
        done
        item="${item:0:$i}"
        #Trim whitespace
        item="${item#"${item%%[![:space:]]*}"}"
        item="${item%"${item##*[![:space:]]}"}"
        if [ -z "$item" ]; then
            continue
        fi
        #Add
        eval "$name+=(\"$item\")"
    done
}

#Parse input
args=()
argc=0
for arg in "$@"; do
    args+=("$arg")
    argc="$(expr $argc + 1)"
done
#Parse options
binDir=""
hdrDir=""
optc=0
while [ $optc -lt $argc ]; do
    arg="${args[$optc]}"
    #Check if not option
    if [ ! "${arg:0:1}" = "-" ]; then
        break
    fi
    optc="$(expr $optc + 1)"
    #--
    if [ "$arg" = "--" ]; then
        break;
    #--bin
    elif [ "$arg" = "--bin" ]; then
        if [ $optc -ge $argc ]; then
            echo "$arg must have an accompanying value" >&2
            exit 1
        fi
        binDir="${args[$optc]}"
        optc="$(expr $optc + 1)"
    #--hdr
    elif [ "$arg" = "--hdr" ]; then
        if [ $optc -ge $argc ]; then
            echo "$arg must have an accompanying value" >&2
            exit 1
        fi
        hdrDir="${args[$optc]}"
        optc="$(expr $optc + 1)"
    #Unsupported
    else
        echo "The option $arg is not supported." >&2
        exit 1
    fi
done
#Parse required
reqc="$(expr $argc - $optc)"
if [ $reqc -lt 1 ]; then
    echo "You must specify a library name." >&2
    exit 1
fi
reqi=$optc
#libName
libName="${args[$reqi]}"
reqi="$(expr $reqi + 1)"

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
allLibs=()
getAllLibs() {
    local libName=$1
    #Ensure library exists
    local libDir="$binSrcDir/$libName"
    if [ ! -d "$libDir" ]; then
        echo "Could not find $libName." >&2
        return
    fi
    #Add to libs (if not already added)
    local lib
    local libAdded=0
    for lib in "${allLibs[@]}"; do
        if [ "$lib" = "$libName" ]; then
            libAdded=1
            break
        fi
    done
    if [ $libAdded = 0 ]; then
        allLibs+=("$libName")
    fi
    #Add deps
    local depsPath="$libDir/deps"
    local deps
    local dep
    if [ -f "$depsPath" ]; then
        getLines deps $depsPath
        for dep in "${deps[@]}"; do
            getAllLibs "$dep"
        done
    fi
}
getAllLibs "$libName"

#Create directories (if needed)
if [ -n "$binDir" ]; then
    mkdir -p "$binDir"
fi
if [ -n "$hdrDir" ]; then
    mkdir -p "$hdrDir"
fi

#Copy libraries
for lib in "${allLibs[@]}"; do
    echo "$lib"
    libDir="$binSrcDir/$lib"
    #Binaries
    if [ -n "$binDir" ]; then
        cp -u "$libDir/$lib$os_ext_lib" "$binDir"
    fi
    #Headers
    if [ -n "$hdrDir" ]; then
        cp -u "$libDir"/*.h "$hdrDir"
    fi
done