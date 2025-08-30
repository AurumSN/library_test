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

## Specification

### C

* `test_initialize` - starting point for `test_context`, used to initialize shared (between implementations) content (`tick` in the example)
* `test_terminate` - terminates the context
* `test_load` - loading of implementations for that context, creates local data of the implementation (not used in the example)
* `test_unload` - unloads the implementation
* `test_foo` and `test_tick` example functions of this project

### C++

`test::context` class is a shell around the C functions with constructors initializing the `m_context` field and loading versions of the implementation (if specified). `load` and `unload` member functions are used for explicit loading and unloading unlike constructors, assignment operatos and destructor which do that implicitly. `foo` and `tick` member functions serve the same purpose as their C counterparts.

Note that incase the function fails the C implementation will assign the value of `context->result` as `test_result_FAILURE` while `test::context` will throw a runtime error.
