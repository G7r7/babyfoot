cmake_minimum_required(VERSION 3.0.0)
project(Babyfoot)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(SOURCE_FILES main.cpp Shader.h Shader.cpp)
set(SOURCE_FILES main.cpp)

set(LIBS_DIR C:/Dvlp/libs)

set(GLAD_ROOT_DIR ${LIBS_DIR}/glad )
set(GLFW_ROOT_DIR ${LIBS_DIR}/glfw-3.3.5 )

set(GLAD_INCLUDE_DIRS ${GLAD_ROOT_DIR}/include)
set(GLFW_INCLUDE_DIRS ${GLFW_ROOT_DIR}/include)

# set(GLAD_LIBRARY ${GLAD_ROOT_DIR}/lib/libglew32.a)
set(GLFW_LIBRARY ${GLFW_ROOT_DIR}/build/src/libglfw3dll.a)


include_directories(${GLAD_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

add_executable(babyfoot ${SOURCE_FILES})

target_link_libraries(babyfoot ${GLEW_LIBRARY} ${GLFW_LIBRARY})