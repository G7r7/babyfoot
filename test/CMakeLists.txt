# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

add_executable(tests main.test.cpp)

add_subdirectory(engine)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

#glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(glm)

target_link_libraries(tests gtest)
include_directories(babyfoot PUBLIC "${glm_SOURCE_DIR}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(tests -static-libgcc)
    target_link_libraries(tests -static-libstdc++)
    #file(COPY /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll DESTINATION .)
endif()

SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")