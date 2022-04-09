#!/bin/bash

function image(){
    docker build --tag babyfoot .
}

function run(){
    docker run --rm -it --name babyfoot \
    --volume .:/home/babyfoot \
    babyfoot \
    "$@"
}

"$@"