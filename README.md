# Babyfoot

## Docker environment

### Install environment
```bash
./docker run
```
### Build
#### Compile for Linux
```bash
mkdir build && cd build
cmake ..
make
```
#### Compile for Windows
```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/x86_64-w64-mingw32.cmake
make
```