FROM gcc:9

RUN apt-get update && apt-get -y install \
    git make cmake unzip gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64

#glfw
WORKDIR "/tmp"
RUN apt-get -y install xorg-dev \
    && wget https://github.com/glfw/glfw/releases/download/3.3.6/glfw-3.3.6.zip \
    && unzip glfw-3.3.6.zip \
    && rm glfw-3.3.6.zip
WORKDIR "/tmp/glfw-3.3.6"
RUN mkdir build && mkdir mingw
WORKDIR "/tmp/glfw-3.3.6/build"
RUN cmake .. \
        -D GLFW_BUILD_EXAMPLES=false \
        -D GLFW_BUILD_TESTS=false \
        # -D GLFW_BUILD_DOCS=false \
        -D GLFW_INSTALL=false \
    && make
WORKDIR "/tmp/glfw-3.3.6/mingw"
RUN cmake .. \
        -D CMAKE_TOOLCHAIN_FILE=CMake/x86_64-w64-mingw32.cmake \
        -D GLFW_BUILD_EXAMPLES=false \
        -D GLFW_BUILD_TESTS=false \
        -D GLFW_BUILD_DOCS=false \
        -D GLFW_INSTALL=false \
    && make

#glad
WORKDIR "/tmp"
RUN wget https://github.com/Dav1dde/glad/archive/refs/tags/v0.1.36.zip \
    && unzip v0.1.36.zip \
    && rm v0.1.36.zip
WORKDIR "/tmp/glad-0.1.36"
RUN mkdir build
WORKDIR "/tmp/glad-0.1.36/build"
RUN cmake .. && make

#glm
WORKDIR "/tmp"
RUN wget https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
RUN unzip glm-0.9.9.8.zip && rm glm-0.9.9.8.zip
   
#stb
WORKDIR "/tmp"
RUN git clone https://github.com/nothings/stb

#assimp
WORKDIR "/tmp"
RUN wget https://github.com/assimp/assimp/archive/refs/tags/v5.1.0.zip
RUN unzip v5.1.0.zip && rm v5.1.0.zip
WORKDIR "/tmp/assimp-5.1.0"
RUN mkdir build && mkdir mingw
WORKDIR "/tmp/assimp-5.1.0/build"
RUN cmake .. \
        # -D BUILD_SHARED_LIBS=OFF \
        -D ASSIMP_BUILD_ASSIMP_TOOLS=OFF \
        -D ASSIMP_NO_EXPORT=ON \
        -D ASSIMP_BUILD_TESTS=OFF \
        -D ASSIMP_BUILD_ZLIB=ON \
        -D ASSIMP_INSTALL_PDB=OFF \
    && make -j6
WORKDIR "/tmp/assimp-5.1.0/mingw"
RUN cmake .. \
        -D CMAKE_SYSTEM_NAME=Windows \
        -D CMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -D CMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
        # -D BUILD_SHARED_LIBS=OFF \
        -D ASSIMP_BUILD_ASSIMP_TOOLS=OFF \
        -D ASSIMP_NO_EXPORT=ON \
        -D ASSIMP_BUILD_TESTS=OFF \
        -D ASSIMP_BUILD_ZLIB=ON \
        -D ASSIMP_INSTALL_PDB=OFF \
    && make -j6


#Adding header files to usr/include/ for intellisense
RUN cp -r /tmp/glfw-3.3.6/include/GLFW /usr/include \
    && cp -r /tmp/glad-0.1.36/build/include/* /usr/include/ \
    && cp -r /tmp/glm/glm/ /usr/include/ \
    && cp -r /tmp/stb/* /usr/include \
    && cp -r /tmp/assimp-5.1.0/include/* /usr/include

COPY ./entrypoint.sh /entrypoint.sh
RUN chmod u+x /entrypoint.sh

WORKDIR "/home/babyfoot/build"