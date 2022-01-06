cmake_minimum_required(VERSION 3.0.0)
project(Babyfoot)

set(SOURCE_FILES src/main.cpp 
    src/shader.hpp src/shader.cpp 
    src/stb_image.h 
    src/stb.cpp 
    src/models/loaded_model.cpp
    src/models/pyramid_model.cpp
)

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/../libs)

set(GLAD_ROOT_DIR ${LIBS_DIR}/glad)
set(GLFW_ROOT_DIR ${LIBS_DIR}/glfw)
set(GLM_ROOT_DIR ${LIBS_DIR}/glm)

set(GLAD_INCLUDE_DIRS ${GLAD_ROOT_DIR}/include)
set(GLFW_INCLUDE_DIRS ${GLFW_ROOT_DIR}/include)
set(GLM_INCLUDE_DIRS ${GLM_ROOT_DIR}/glm)

add_library(glad ${GLAD_ROOT_DIR}/src/glad.c)
if(WIN32)
    set(GLFW_LIBRARY ${GLFW_ROOT_DIR}/build/src/libglfw3dll.a)
else()
    set(GLFW_LIBRARY ${GLFW_ROOT_DIR}/build/src/libglfw3.a)
endif()

include_directories(${GLAD_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

add_executable(babyfoot ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(babyfoot glad ${GLFW_LIBRARY})
else()
    target_link_libraries(babyfoot glad ${GLFW_LIBRARY} dl pthread)
endif()