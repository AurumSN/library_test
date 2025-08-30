# A simple example of a multi-so library

This project is an example of how to write libraries with several implementations for multiple contexts such as different Graphics APIs (like DirectX, Vulkan, etc).

The base of the example is written in C with a CPP "shell".

## Build

The build process is as simple as possible with CMake:

### Unix

* Execute commands:
```
mkdir build
cd build
cmake ..
make
```

### Windows

* Execute commands:
```
mkdir build
cd build
cmake ..
```

* Open `build\library_test.sln`
* Right click `ALL_BUILD` -> build

## Running

### Unix

* Execute commands `./tests_c` or `./tests_cpp`

### Windows

* Right click `tests_c` or `tests_cpp` -> Set as Startup Project
* Run