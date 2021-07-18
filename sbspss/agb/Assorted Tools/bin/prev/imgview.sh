#!sh

if bmp2prev -o data.txt $*
then
    if prev.sh data.txt
    then
        return 0
    else
        return 1
    fi
else
    echo "!! Error in bmp2prev.exe so command stopped."
    return 1
fi
