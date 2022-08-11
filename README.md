# Babyfoot
## Build
```shell
mkdir build && cd build
cmake .. && make -j
```
## Cross-compilation
### On Linux for Windows
```shell
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../x86_64-w64-mingw32-posix.cmake .. && make -j
```