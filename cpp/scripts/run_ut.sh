#!/bin/bash

basepath=$(cd `dirname $0`/../; pwd)

cd $basepath/

main() {
    mkdir -p cmake_build/
    cd cmake_build/
    cmake .. -DENABLE_UNIT_TESTS=ON || {
        error_exit "Failed to cmake."
    }
    cmake --build . || {
        error_exit "Failed to make."
    }
    ./tests_darabonba_util || {
        error_exit "Failed to test."
    }
}

error_exit() {
    echo
    echo Error: "$@"
    echo "----------------------------------------------------------------------"
    echo
    exit 1
}

main "$@"
exit 0
