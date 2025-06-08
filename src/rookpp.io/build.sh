masterDir="$(dirname $PWD)"
masterName=_master._.sh
while [ ! -f "$masterDir/$masterName" ]
do
    masterDir="$(dirname $masterDir)"
done
bash "$masterDir/$masterName" "$(realpath $0)"