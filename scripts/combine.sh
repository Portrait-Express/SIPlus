#! /usr/bin/bash

AR=`which ar`
RANLIB=`which ranlib`

EM_TEST=0
IS_WASM=

configure_wasm() {
    FILE=$1
    if [[ $EM_TEST == 1 ]]; then return 0; fi

    if [[ $FILE == '' ]]; then
        echo 'invalid library to add_library' >& 2
        return 1
    fi

    if ! [[ -f $FILE ]]; then
        echo "File $1 does not exist" >& 2
        return 1
    fi

    EM_TEST=1
    WASM_COUNT=`file $FILE | grep wasm | wc -l`

    if [[ $WASM_COUNT -gt 0 ]]; then
        echo "Detected wasm object files. Using emar and emranlib."
        IS_WASM=1

        AR=`which emar`
        RANLIB=`which emranlib`
    fi
}

add_library() {
    if [[ $1 == '' ]]; then
        echo 'invalid library to add_library' >& 2
        return 1
    fi

    if ! [[ -f $1 ]]; then
        echo "File $1 does not exist" >& 2
        return 1
    fi

    LIB=$1

    while IFS= read -r i; do 
        COUNT=`echo "$i" | awk '{print $1}'`
        FILE=`echo "$i" | awk '{print $2}'`

        for n in `seq 1 $COUNT`; do 
            $AR xN $n $LIB $FILE; 

            configure_wasm $FILE;

            echo "Adding ${IS_WASM:+(wasm)} $FILE - $n"; 
            $AR q $OUTPUT $FILE; 
            rm $FILE; 
        done; 

        emranlib $OUTPUT;
    done < <(ar t $1 | sort | uniq -c)
}

help() {
    echo "usage: combine.sh"
    echo 
    echo "Run this in your build directory to add the object files from antlr to libsiplus.a"
    echo "in order to create a \"fat\" static library that contains antlr for simpler linking."
    echo "Requires you to be building either as WASM or as a static library."
    echo
    echo "Enironment Variables:"
    echo "    BUILD_DIR         Set to your build directory to use a different directory than the working directory"
    echo "    OUTPUT            The path to libsiplus.a (or other .a archive to add antlr to)"
    exit 0
}

for arg in "$@"; do
    case $arg in
    "-h"|"--help")
        help
        ;;
    esac
done

BUILD_DIR=${BUILD_DIR:-$(pwd)}
OUTPUT=${OUTPUT:-$BUILD_DIR/libsiplus.a}

add_library "$BUILD_DIR/dependencies/antlr4/runtime/Cpp/runtime/libantlr4-runtime.a"

echo "Running ranlib for $OUTPUT";
$RANLIB $OUTPUT
