shPath=$BASH_SOURCE
shDir="$(dirname "$shPath")"

outputDir="$1"
for inputPath in "${@:2}"; do
    outputPath="$outputDir/$(basename $inputPath)"
    if [ "$inputPath" -nt "$outputPath" ]; then
        echo Copying "$inputPath"
        cp "$inputPath" "$outputPath"
    fi
done