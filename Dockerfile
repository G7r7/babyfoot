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
        -D ASSIMP_BUILD_3DS_IMPORTER=OFF \
        -D ASSIMP_BUILD_AMF_IMPORTER=OFF \
        -D ASSIMP_BUILD_AC_IMPORTER=OFF \
        -D ASSIMP_BUILD_ASE_IMPORTER=OFF \
        -D ASSIMP_BUILD_ASSBIN_IMPORTER=OFF \
        -D ASSIMP_BUILD_B3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_BVH_IMPORTER=OFF \
        -D ASSIMP_BUILD_COLLADA_IMPORTER=OFF \
        -D ASSIMP_BUILD_DXF_IMPORTER=OFF \
        -D ASSIMP_BUILD_CSM_IMPORTER=OFF \
        -D ASSIMP_BUILD_HMP_IMPORTER=OFF \
        -D ASSIMP_BUILD_IRRMESH_IMPORTER=OFF \
        -D ASSIMP_BUILD_IRR_IMPORTER=OFF \
        -D ASSIMP_BUILD_LWO_IMPORTER=OFF \
        -D ASSIMP_BUILD_LWS_IMPORTER=OFF \
        -D ASSIMP_BUILD_M3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_MD2_IMPORTER=OFF \
        -D ASSIMP_BUILD_MD3_IMPORTER=OFF \
        -D ASSIMP_BUILD_MD5_IMPORTER=OFF \
        -D ASSIMP_BUILD_MDC_IMPORTER=OFF \
        -D ASSIMP_BUILD_MDL_IMPORTER=OFF \
        -D ASSIMP_BUILD_NFF_IMPORTER=OFF \
        -D ASSIMP_BUILD_NDO_IMPORTER=OFF \
        -D ASSIMP_BUILD_OFF_IMPORTER=OFF \
        -D ASSIMP_BUILD_OBJ_IMPORTER=ON \
        -D ASSIMP_BUILD_OGRE_IMPORTER=OFF \
        -D ASSIMP_BUILD_OPENGEX_IMPORTER=OFF \
        -D ASSIMP_BUILD_PLY_IMPORTER=OFF \
        -D ASSIMP_BUILD_MS3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_COB_IMPORTER=OFF \
        -D ASSIMP_BUILD_BLEND_IMPORTER=OFF \
        -D ASSIMP_BUILD_IFC_IMPORTER=OFF \
        -D ASSIMP_BUILD_XGL_IMPORTER=OFF \
        -D ASSIMP_BUILD_FBX_IMPORTER=OFF \
        -D ASSIMP_BUILD_Q3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_Q3BSP_IMPORTER=OFF \
        -D ASSIMP_BUILD_RAW_IMPORTER=OFF \
        -D ASSIMP_BUILD_SIB_IMPORTER=OFF \
        -D ASSIMP_BUILD_SMD_IMPORTER=OFF \
        -D ASSIMP_BUILD_STL_IMPORTER=OFF \
        -D ASSIMP_BUILD_TERRAGEN_IMPORTER=OFF \
        -D ASSIMP_BUILD_3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_X_IMPORTER=OFF \
        -D ASSIMP_BUILD_X3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_GLTF_IMPORTER=OFF \
        -D ASSIMP_BUILD_3MF_IMPORTER=OFF \
        -D ASSIMP_BUILD_MMD_IMPORTER=OFF \
        -D ASSIMP_BUILD_ASSIMP_TOOLS=OFF \
        -D ASSIMP_NO_EXPORT=ON \
        -D ASSIMP_BUILD_TESTS=OFF \
        -D ASSIMP_BUILD_ZLIB=ON \
        -D ASSIMP_INSTALL_PDB=OFF \
        && make -j
WORKDIR "/tmp/assimp-5.1.0/mingw"
RUN cmake .. \
        -D CMAKE_SYSTEM_NAME=Windows \
        -D CMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -D CMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
        # -D BUILD_SHARED_LIBS=OFF \
        -D ASSIMP_BUILD_3DS_IMPORTER=OFF \
        -D ASSIMP_BUILD_AMF_IMPORTER=OFF \
        -D ASSIMP_BUILD_AC_IMPORTER=OFF \
        -D ASSIMP_BUILD_ASE_IMPORTER=OFF \
        -D ASSIMP_BUILD_ASSBIN_IMPORTER=OFF \
        -D ASSIMP_BUILD_B3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_BVH_IMPORTER=OFF \
        -D ASSIMP_BUILD_COLLADA_IMPORTER=OFF \
        -D ASSIMP_BUILD_DXF_IMPORTER=OFF \
        -D ASSIMP_BUILD_CSM_IMPORTER=OFF \
        -D ASSIMP_BUILD_HMP_IMPORTER=OFF \
        -D ASSIMP_BUILD_IRRMESH_IMPORTER=OFF \
        -D ASSIMP_BUILD_IRR_IMPORTER=OFF \
        -D ASSIMP_BUILD_LWO_IMPORTER=OFF \
        -D ASSIMP_BUILD_LWS_IMPORTER=OFF \
        -D ASSIMP_BUILD_M3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_MD2_IMPORTER=OFF \
        -D ASSIMP_BUILD_MD3_IMPORTER=OFF \
        -D ASSIMP_BUILD_MD5_IMPORTER=OFF \
        -D ASSIMP_BUILD_MDC_IMPORTER=OFF \
        -D ASSIMP_BUILD_MDL_IMPORTER=OFF \
        -D ASSIMP_BUILD_NFF_IMPORTER=OFF \
        -D ASSIMP_BUILD_NDO_IMPORTER=OFF \
        -D ASSIMP_BUILD_OFF_IMPORTER=OFF \
        -D ASSIMP_BUILD_OBJ_IMPORTER=ON \
        -D ASSIMP_BUILD_OGRE_IMPORTER=OFF \
        -D ASSIMP_BUILD_OPENGEX_IMPORTER=OFF \
        -D ASSIMP_BUILD_PLY_IMPORTER=OFF \
        -D ASSIMP_BUILD_MS3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_COB_IMPORTER=OFF \
        -D ASSIMP_BUILD_BLEND_IMPORTER=OFF \
        -D ASSIMP_BUILD_IFC_IMPORTER=OFF \
        -D ASSIMP_BUILD_XGL_IMPORTER=OFF \
        -D ASSIMP_BUILD_FBX_IMPORTER=OFF \
        -D ASSIMP_BUILD_Q3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_Q3BSP_IMPORTER=OFF \
        -D ASSIMP_BUILD_RAW_IMPORTER=OFF \
        -D ASSIMP_BUILD_SIB_IMPORTER=OFF \
        -D ASSIMP_BUILD_SMD_IMPORTER=OFF \
        -D ASSIMP_BUILD_STL_IMPORTER=OFF \
        -D ASSIMP_BUILD_TERRAGEN_IMPORTER=OFF \
        -D ASSIMP_BUILD_3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_X_IMPORTER=OFF \
        -D ASSIMP_BUILD_X3D_IMPORTER=OFF \
        -D ASSIMP_BUILD_GLTF_IMPORTER=OFF \
        -D ASSIMP_BUILD_3MF_IMPORTER=OFF \
        -D ASSIMP_BUILD_MMD_IMPORTER=OFF \
        -D ASSIMP_BUILD_ASSIMP_TOOLS=OFF \
        -D ASSIMP_NO_EXPORT=ON \
        -D ASSIMP_BUILD_TESTS=OFF \
        -D ASSIMP_BUILD_ZLIB=ON \
        -D ASSIMP_INSTALL_PDB=OFF \
        && make -j

#Adding header files to usr/include/ for intellisense
RUN cp -r /tmp/glfw-3.3.6/include/GLFW /usr/include \
    && cp -r /tmp/glad-0.1.36/build/include/* /usr/include/ \
    && cp -r /tmp/glm/glm/ /usr/include/ \
    && cp -r /tmp/stb/* /usr/include \
    && cp -r /tmp/assimp-5.1.0/include/* /usr/include

COPY ./entrypoint.sh /entrypoint.sh
RUN chmod u+x /entrypoint.sh

WORKDIR "/home/babyfoot/build"