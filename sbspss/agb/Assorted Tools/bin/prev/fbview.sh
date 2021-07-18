#!sh

if bmp2fb -o fbdata.txt $*
then
    if prev.sh fbdata.txt
    then
        return 0
    else
        return 1
    fi
else
    echo "!! Error in bmp2fb.exe so command stopped."
    return 1
fi
