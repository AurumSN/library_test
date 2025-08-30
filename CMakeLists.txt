cmake_minimum_required(VERSION 3.10)

project(library_test C CXX)

add_library(test_impl_a SHARED src/test_impl.c)

target_compile_definitions(test_impl_a PRIVATE VERSION_A)

add_library(test_impl_b SHARED src/test_impl.c)

target_compile_definitions(test_impl_b PRIVATE VERSION_B)

add_library(test STATIC src/test.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(test PRIVATE TEST_IMPL_A_FILEPATH="$<TARGET_FILE:test_impl_a>")
target_compile_definitions(test PRIVATE TEST_IMPL_B_FILEPATH="$<TARGET_FILE:test_impl_b>")

add_library(test_cpp STATIC src/test.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_cpp PRIVATE test)

add_executable(tests_c tests/main.c)

target_link_libraries(tests_c PRIVATE test)

add_executable(tests_cpp tests/main.cpp)

target_link_libraries(tests_cpp PRIVATE test_cpp)