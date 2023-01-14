FROM gcc:12.1-bullseye

RUN apt-get update && apt-get -y install \
    git make cmake ninja-build unzip gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 \
    python3-pip

RUN apt-get -y install xorg-dev

RUN apt-get update && apt-get -y install gdb

#Gcovr
RUN pip install gcovr

WORKDIR "/home/babyfoot/build"

RUN useradd -ms /bin/bash dev
USER dev
