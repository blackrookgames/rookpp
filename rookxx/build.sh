shPath="$(realpath $BASH_SOURCE)"
shDir="$(dirname $shPath)"
if [ ! "$PWD" = "$shDir" ]; then
    oldDir="$PWD"
    cd "$shDir"
    bash "$shPath" "$@"
    result="$?"
    cd "$oldDir"
    exit $result
fi

binDir=bin
objDir=obj
hdrDir=hdr
srcDir=src

declare -a libSrcRPaths
libSrcRPaths+=("collection/voidptr/VoidPtrConstIterator.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrIterator.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrList.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrListConstIterator.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrListIterator.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrQueue.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrSegCol.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrSegColConstIterator.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrSegColIterator.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrSegColSegment.cpp")
libSrcRPaths+=("collection/voidptr/VoidPtrStack.cpp")
libSrcRPaths+=("bitman/BitPnt.cpp")
libSrcRPaths+=("bitman/BitPtr.cpp")
libSrcRPaths+=("bitman/ConstBitPnt.cpp")
libSrcRPaths+=("bitman/ConstBitPtr.cpp")
libSrcRPaths+=("strm/OFSWriter.cpp")
libSrcRPaths+=("strm/IFSReader.cpp")

#Config

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    osExe=
    osLib=.so
elif [[ "$OSTYPE" == "cygwin" ]]; then
    osExe=.exe
    osLib=.dll
elif [[ "$OSTYPE" == "msys" ]]; then
    osExe=.exe
    osLib=.dll
else
    echo "Unknown OS: $OS_TYPE" 1>&2
    exit 1
fi

libPath="$binDir/test$osExe"

declare -a libObjAPaths
for path in "${libSrcRPaths[@]}"; do
    libObjAPaths+=("$objDir/${path%.c}.o")
done

#Clean

if [ "$1" = "clean" ]; then
    rm -fr "$objDir" "$libPath"
    exit
fi

#Build test

for i in "${!libSrcRPaths[@]}"; do
    libSrcRPath="$srcDir/${libSrcRPaths[$i]}"
    libObjAPath="${libObjAPaths[$i]}"
    mkdir -p "$(dirname $libObjAPath)"
    g++ -c "$libSrcRPath" -o "$libObjAPath" -I"$hdrDir"
    if [ ! "$?" = 0 ]; then exit 1; fi
done

mkdir -p "$binDir"
g++ "test.cpp" "${libObjAPaths[@]}" -o "$libPath" -I"$hdrDir"
if [ ! "$?" = 0 ]; then exit 1; fi