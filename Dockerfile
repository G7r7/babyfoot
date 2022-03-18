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
RUN cp -r include/GLFW /usr/include
RUN mkdir build && mkdir mingw
WORKDIR "/tmp/glfw-3.3.6/build"
RUN cmake .. \
        -D GLFW_BUILD_EXAMPLES=false \
        -D GLFW_BUILD_TESTS=false \
        -D GLFW_BUILD_DOCS=false \
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
WORKDIR "/tmp/glm"
   
#stb
WORKDIR "/tmp"
RUN git clone https://github.com/nothings/stb

WORKDIR /home/babyfoot