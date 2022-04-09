#!/bin/bash

function build(){
    docker build --tag babyfoot .
}

function start(){
    docker run --rm -it --name babyfoot \
    --volume $(pwd):/home/babyfoot
    --entrypoint /bin/bash \
    babyfoot
}

function run(){
    docker run --rm -it --name babyfoot \
    --volume $(pwd):/home/babyfoot \
    --workdir="/home/babyfoot/build" \
    babyfoot \
    "$@"
}

"$@"