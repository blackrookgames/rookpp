shPath="$(realpath $0)"
if [ -z "$1" ]; then
echo "$(basename $shPath) <makePath>"
exit
fi

makePath="$1"

echo "CC = g++" >>"$makePath"
echo "CFLAGS = -Wall -Wno-unknown-pragmas -g" >>"$makePath"
echo "" >>"$makePath"

echo -e "\tGet source directories"
srcDir="$(dirname $makePath)"
echo "SRCDIR = $srcDir" >>"$makePath"
#Get source directory
srcSourceDir="$srcDir/source"
srcSourceDir_r="\$(SRCDIR)/$(realpath -m --relative-to=$srcDir $srcSourceDir)"
echo "SRCSOURCEDIR = $srcSourceDir_r" >>"$makePath"
#Get source header directory
srcHeaderDir="$srcDir/header"
srcHeaderDir_r="\$(SRCDIR)/$(realpath -m --relative-to=$srcDir $srcHeaderDir)"
echo "SRCHEADERDIR = $srcHeaderDir_r" >>"$makePath"
#Get included header directory
srcIncludeDir="$srcDir/include"
srcIncludeDir_r="\$(SRCDIR)/$(realpath -m --relative-to=$srcDir $srcIncludeDir)"
echo "SRCINCLUDEDIR = $srcIncludeDir_r" >>"$makePath"
#Get object directory
srcObjectDir="$srcDir/object"
srcObjectDir_r="\$(SRCDIR)/$(realpath -m --relative-to=$srcDir $srcObjectDir)"
echo "SRCOBJECTDIR = $srcObjectDir_r" >>"$makePath"
#Blank line
echo "" >>"$makePath"

echo -e "\tGet master directory"
#Get master directory
masterDir="$(dirname $shPath)"
echo "MASTERDIR = $masterDir" >>"$makePath"
#Get master bin directory
masterBinDir="$masterDir/bin"
masterBinDir_r="\$(MASTERDIR)/$(realpath -m --relative-to=$masterDir $masterBinDir)"
echo "MASTERBINDIR = $masterBinDir_r" >>"$makePath"
#Blank line
echo "" >>"$makePath"

echo -e "\tDetermine save path for binary"
#Get save name of binary
binName="$(basename $srcDir)"
#Get save directory of binary
binDir="$masterBinDir/$binName"
binDir_r="\$(MASTERBINDIR)/$(realpath -m --relative-to=$masterBinDir $binDir)"
echo "BINDIR = $binDir_r" >>"$makePath"
#Get save path of binary
binPath="$binDir/$binName.dll"
binPath_r="\$(BINDIR)/$(realpath -m --relative-to=$binDir $binPath)"
echo "BINPATH = $binPath_r" >>"$makePath"
#Blank line
echo "" >>"$makePath"

echo -e "\tGet dependencies"
#Get dependencies
mkdir -p $srcIncludeDir
srcDepsFile="$srcDir/deps.txt"
srcDepsFile_r="\$(SRCDIR)/$(realpath -m --relative-to=$srcDir $srcDepsFile)"
echo "SRCDEPSFILE = $srcDepsFile_r" >>"$makePath"
binDepsFile="$binDir/$binName.deps.txt"
binDepsFile_r="\$(BINDIR)/$(realpath -m --relative-to=$binDir $binDepsFile)"
echo "BINDEPSFILE = $binDepsFile_r" >>"$makePath"
getDeps() {
    while read -n 1 char; do
        if [ ! -z "${char//[[:space:]]/}" ]; then
            echo -n "$char"
        else
            echo -n " "
        fi
    done < "$1"
}
IFS=' ' read -r -a dependencies <<< "$(getDeps "$srcDepsFile")"
IFS=
#Loop thru dependencies
dependencyArgs="-L \$(MASTERBINDIR)"
for dependency in ${dependencies[@]}; do
    echo -e "\t\t$dependency"
    dependencyArgs+=" -l $dependency/$dependency"
    cp -u $masterBinDir/$dependency/*.h $srcIncludeDir
    echo -e "DEPENDENCYARGS = $dependencyArgs" >>"$makePath"
done
#Blank line
echo "" >>"$makePath"

echo -e "\tGet source files"
#Get source files
srcSourcePaths=()
srcSourcePaths_r=()
echo -n "SRCSOURCEPATHS =" >>"$makePath"
for srcSourcePath in $srcSourceDir/*.cpp; do
    if [ -f "$srcSourcePath" ]; then
        srcSourcePath_r="\$(SRCSOURCEDIR)/$(basename $srcSourcePath)"
        srcSourcePaths+=("$srcSourcePath")
        srcSourcePaths_r+=("$srcSourcePath_r")
        echo " \\" >>"$makePath"
        echo -n "$srcSourcePath_r" >>"$makePath"
    fi
done
echo "" >>"$makePath"
#Get source header files
srcHeaderPaths=()
srcHeaderPaths_r=()
echo -n "SRCHEADERPATHS =" >>"$makePath"
for srcHeaderPath in $srcHeaderDir/*.h; do
    if [ -f "$srcHeaderPath" ]; then
        srcHeaderPath_r="\$(SRCHEADERDIR)/$(basename $srcHeaderPath)"
        srcHeaderPaths+=("$srcHeaderPath")
        srcHeaderPaths_r+=("$srcHeaderPath_r")
        echo " \\" >>"$makePath"
        echo -n "$srcHeaderPath_r" >>"$makePath"
    fi
done
echo "" >>"$makePath"
#Get included header files
srcIncludePaths=()
srcIncludePaths_r=()
echo -n "SRCINCLUDEPATHS =" >>"$makePath"
for srcIncludePath in $srcIncludeDir/*.h; do
    if [ -f "$srcIncludePath" ]; then
        srcIncludePath_r="\$(SRCINCLUDEDIR)/$(basename $srcIncludePath)"
        srcIncludePaths+=("$srcIncludePath")
        srcIncludePaths_r+=("$srcIncludePath_r")
        echo " \\" >>"$makePath"
        echo -n "$srcIncludePath_r" >>"$makePath"
    fi
done
echo "" >>"$makePath"
#Get paths for object files
srcObjectPaths=()
srcObjectPaths_r=()
echo -n "SRCOBJECTPATHS =" >>"$makePath"
for srcSourcePath in "${srcSourcePaths[@]}"; do
    srcObjectPath="$srcObjectDir/$(basename ${srcSourcePath%.*}.o)"
    srcObjectPath_r="\$(SRCOBJECTDIR)/$(basename $srcObjectPath)"
    srcObjectPaths+=("$srcObjectPath")
    srcObjectPaths_r+=("$srcObjectPath_r")
    echo " \\" >>"$makePath"
    echo -n "$srcObjectPath_r" >>"$makePath"
done
echo "" >>"$makePath"
#Blank line
echo "" >>"$makePath"

echo -e "\tDetermine save paths for headers"
#Get save paths of headers within binary save directory
binHeaderPaths=()
binHeaderPaths_r=()
echo -n "BINHEADERPATHS =" >>"$makePath"
for srcHeaderPath in "${srcHeaderPaths[@]}"; do
    binHeaderPath="$binDir/$(basename $srcHeaderPath)"
    binHeaderPath_r="\$(BINDIR)/$(basename $srcHeaderPath)"
    binHeaderPaths+=("$binHeaderPath")
    binHeaderPaths_r+=("$binHeaderPath_r")
    echo " \\" >>"$makePath"
    echo -n "$binHeaderPath_r" >>"$makePath"
done
echo "" >>"$makePath"
#Blank line
echo "" >>"$makePath"

echo -e "\tCreate binary recipe"
#Binary recipe
echo -e "\$(BINPATH): $binDepsFile \$(BINHEADERPATHS) \$(SRCOBJECTPATHS)" >>"$makePath"
echo -e "\t@echo -e \"\\\t\$(BINPATH)\"" >>"$makePath"
echo -e "\t@\$(CC) \$(CFLAGS) -fpic -shared \$(SRCOBJECTPATHS) -o \$(BINPATH) \$(DEPENDENCYARGS)" >>"$makePath"
echo "" >>"$makePath"

echo -e "\tCreate dependencies recipe"
#Dependencies recipe
echo -e "\$(BINDEPSFILE): \$(SRCDEPSFILE)" >>"$makePath"
echo -e "\t@echo -e \"\\\t\$(BINDEPSFILE)\"" >>"$makePath"
echo -e "\t@cp -u \$(SRCDEPSFILE) \$(BINDEPSFILE)" >>"$makePath"
echo "" >>"$makePath"

echo -e "\tCreate header recipes"
#Header recipes
for i in "${!srcHeaderPaths[@]}"; do
    binHeaderPath_r="$(echo "${binHeaderPaths_r[$i]}" | xargs)"
    srcHeaderPath_r="$(echo "${srcHeaderPaths_r[$i]}" | xargs)"
    echo -e "$binHeaderPath_r: $srcHeaderPath_r" >>"$makePath"
    echo -e "\t@echo -e \"\\\t$binHeaderPath_r\"" >>"$makePath"
    echo -e "\t@cp -u $srcHeaderPath_r $binHeaderPath_r" >>"$makePath"
    echo "" >>"$makePath"
done

echo -e "\tCreate object recipes"
#Objects recipes
for i in "${!srcObjectPaths_r[@]}"; do
    srcObjectPath_r="$(echo "${srcObjectPaths_r[$i]}" | xargs)"
    srcSourcePath_r="$(echo "${srcSourcePaths_r[$i]}" | xargs)"
    echo -e "$srcObjectPath_r: $srcSourcePath_r" >>"$makePath"
    echo -e "\t@echo -e \"\\\t$srcObjectPath_r\"" >>"$makePath"
    echo -e "\t@\$(CC) \$(CFLAGS) -c \$< -o \$@ -I \$(SRCHEADERDIR) -I \$(SRCINCLUDEDIR) \$(DEPENDENCYARGS)" >>"$makePath"
    echo "" >>"$makePath"
done

echo -e "\tCreate clean recipe"
#Clean recipe
echo -e "clean:" >>"$makePath"
echo -e "\t@echo Clean" >>"$makePath"
echo -e "\t@rm -fr \$(SRCOBJECTDIR)" >>"$makePath"
echo -e "\t@rm -fr \$(BINDIR)/*" >>"$makePath"
echo "" >>"$makePath"

echo -e "\tCreate cleanlibs recipe"
#Clean recipe
echo -e "cleanlibs:" >>"$makePath"
echo -e "\t@echo Clean included libraries" >>"$makePath"
echo -e "\t@rm -fr \$(SRCINCLUDEDIR)/*" >>"$makePath"
echo "" >>"$makePath"

echo -e "\tCreate required directories"
mkdir -p "$srcObjectDir"
mkdir -p "$binDir"

#echo -e "export MASTERDIR      := $shDir" >>"$makePath"
#echo -e "export MASTERBINDIR   := $shDir/bin" >>"$makePath"
#echo -e "export SRCDIR         := $makeDir" >>"$makePath"
#echo -e "export BINDIR         := $shDir/bin/$binName" >>"$makePath"
#echo -e "" >>"$makePath"