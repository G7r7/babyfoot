#!/bin/bash

if [[ "$TARGET" == "WINDOWS" ]]
then
    CMAKE_TOOLCHAIN_FILE="-DCMAKE_TOOLCHAIN_FILE=../cmake/x86_64-w64-mingw32.cmake"
fi
if [[ "$BUILD" == "DEBUG" ]]
then
    CMAKE_BUILD_TYPE="-DCMAKE_BUILD_TYPE=Debug"
fi

function config(){
    cmake .. $CMAKE_TOOLCHAIN_FILE $CMAKE_BUILD_TYPE
}

function compile(){
    make -j6
}

function build(){
    config && compile
}

function headers(){
    cp -r /usr/include /home/babyfoot/headerfiles
}

"$@"