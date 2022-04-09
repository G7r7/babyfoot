#!/bin/bash

function config(){
    echo "Running cmake..."
    cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/x86_64-w64-mingw32.cmake -DCMAKE_BUILD_TYPE=Debug
}

function compile(){
    echo "Running make..."
    make -j6
}

function build(){
    config && compile
}

function headers(){
    cp -r /usr/include /home/babyfoot/headerfiles
}

"$@"