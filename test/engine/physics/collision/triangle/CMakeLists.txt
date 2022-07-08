cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE SOURCE_FILES ./*.cpp)
target_sources(tests PUBLIC ${SOURCE_FILES})
target_sources(tests PUBLIC ${CMAKE_SOURCE_DIR}/src/engine/physics/collision/triangle/triangle_collision.cpp)