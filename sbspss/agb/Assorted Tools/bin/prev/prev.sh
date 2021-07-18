#!sh

if prevcl -o ../../src/bin/prev/agb/agbprev/prevdata.c $1
then
    cd ../../src/bin/prev/agb/agbprev
    if make
    then
        cd ../../../../../bin/prev
        return 0
    else
        echo "!! Error in make so command stopped."
        cd ../../../../../bin/prev
        return 1
    fi
else
    echo "!! Error in prevcl.exe so command stopped."
    return 1
fi
