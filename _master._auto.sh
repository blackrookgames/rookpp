shPath="$(realpath $0)"
if [ -z "$1" ]; then
echo "$(basename $shPath) <autoPath>"
exit
fi

autoPath="$1"
autoDir="$(dirname $autoPath)"

inputFiles=()
outputFiles=()

indent="    "

getFiles() {
    local _name=$1
    local _files=()
    local _absFile=
    local _relFile=
    readarray -t _files <<< "$(find "$autoDir" -type f -name $_name)"
    for _absFile in ${_files[@]}; do
        _relFile="$(realpath -m --relative-to=$autoDir $_absFile)"
        inputFiles+=("\$(DIRECTORY)/$_relFile")
        outputFiles+=("\$(DIRECTORY)/${_relFile%.*}")
    done
}

recipe() {
    local _inputFile=$1
    local _outputFile=$2
    echo -e "${_outputFile}: ${_inputFile}"
    echo -e "\t@echo -e \"\\\t${_outputFile}\""
    echo -e "\t@sh \"${_inputFile}\" \"${_outputFile}\""
}

getFiles "*.h.sh"
getFiles "*.cpp.sh"

echo -e "DIRECTORY = ${autoDir}" >>$autoPath
echo -e "" >>$autoPath

echo -e -n "all:" >>$autoPath
for i in "${!outputFiles[@]}"; do
    echo -e " \\" >>$autoPath
    echo -e -n "${outputFiles[$i]}" >>$autoPath
done
echo -e "" >>$autoPath
echo -e "\t @echo >>/dev/null" >>$autoPath

for i in "${!outputFiles[@]}"; do
    echo -e "" >>$autoPath
    echo "$(recipe "${inputFiles[$i]}" "${outputFiles[$i]}")" >>$autoPath
done