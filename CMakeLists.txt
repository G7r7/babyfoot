cmake_minimum_required(VERSION 3.0.0)
project(Babyfoot)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(babyfoot ${SOURCE_FILES})

include_directories(/tmp/glad-0.1.36/build/include/ /tmp/glm/ /tmp/glfw-3.3.6/include/ /tmp/stb/ /tmp/assimp-3.1.1/include/)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(babyfoot /tmp/glfw-3.3.6/mingw/src/libglfw3.a)
    target_link_libraries(babyfoot /tmp/assimp-3.1.1/mingw/code/libassimp.dll.a)
    target_link_libraries(babyfoot /tmp/assimp-3.1.1/mingw/contrib/zlib/libzlibstatic.a)
    file(COPY /tmp/assimp-3.1.1/mingw/code/libassimp.dll DESTINATION .)
    else()
    target_link_libraries(babyfoot /tmp/glfw-3.3.6/build/src/libglfw3.a)
    target_link_libraries(babyfoot /tmp/assimp-3.1.1/build/code/libassimp.so)
    file(COPY /tmp/assimp-3.1.1/build/code/libassimp.so DESTINATION .)
    target_link_libraries(babyfoot dl)
    target_link_libraries(babyfoot X11)
    target_link_libraries(babyfoot pthread)
endif()
add_library(glad /tmp/glad-0.1.36/build/src/glad.c)
target_link_libraries(babyfoot glad)

file(COPY /home/babyfoot/src/ressources/ DESTINATION ./ressources)