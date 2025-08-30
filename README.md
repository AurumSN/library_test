# A simple example of a multi-so library

This project is an example of how to write libraries with several implementations for multiple contexts such as different Graphics APIs (like DirectX, Vulkan, etc).

The base of the example is written in C with a CPP "shell".

## Build

The build process is as simple as possible with CMake:

### Unix
```
mkdir build
cd build
cmake ..
make
```

### Windows
```
TODO
```

## Running

### Unix

C Test: `./tests_c`

CPP Test: `./tests_cpp`