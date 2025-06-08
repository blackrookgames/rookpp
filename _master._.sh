shPath="$(realpath $0)"
master="${shPath%.*}"
masterAuto="${master}auto.sh"
masterMake="${master}make.sh"

if [ -z $1 ]; then
    echo "$(basename $0) <basePath>"
    exit
fi

basePath=$1
autoPath="${basePath}.auto"
makePath="${basePath}.make"
rm -f $autoPath $makePath

if [ "$2" = "clean" ]; then
    cleaning=1
else
    cleaning=0
fi

#Auto files
echo "Updating auto files"
bash "$masterAuto" "$autoPath"
make -f "$autoPath"
if [ ! "$?" = "0" ]; then
    exit
fi

#Make file
echo "Preparing make file"
bash "$masterMake" "$makePath"
echo "Running make file"
make -f "$makePath" "${@:2}"
if [ ! "$?" = "0" ]; then
    exit
fi

#Remove created files if cleaning
if [ $cleaning = 1 ]; then
    rm -f "$autoPath"
    rm -f "$makePath"
fi