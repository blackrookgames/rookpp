shPath="$(realpath $0)"
shDir="$(dirname $shPath)"

if [ -z "$1" ]; then
    echo -n "$(basename $shPath)"
    echo " <path>"
    exit
fi

path=$1
content="$(cat "$path")"
#Get lines
mapfile -t rawArray <<< "$content"
for item in "${rawArray[@]}"; do
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
    echo "$item"
done