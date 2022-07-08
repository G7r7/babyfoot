# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

add_executable(tests main.test.cpp)

add_subdirectory(engine)

include_directories(/tmp/googletest-release-1.12.1/googletest/include/)

target_link_libraries(tests /tmp/googletest-release-1.12.1/build/lib/libgtest_main.a)
target_link_libraries(tests /tmp/googletest-release-1.12.1/build/lib/libgtest.a)
target_link_libraries(tests pthread)

SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")