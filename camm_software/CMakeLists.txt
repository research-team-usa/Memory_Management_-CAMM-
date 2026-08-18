cmake_minimum_required(VERSION 3.16)
project(camm VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads REQUIRED)
add_library(camm STATIC
 src/store/disk_store.cpp src/store/io_uring_engine.cpp src/store/recovery.cpp
 src/cache/ram_cache.cpp src/cache/prefix_cache.cpp src/cache/single_flight.cpp
 src/policy/adaptive_policy.cpp src/observer/cupti_observer.cpp src/observer/system_observer.cpp
 src/adapter/llama_adapter.cpp src/metrics/metrics.cpp)
target_include_directories(camm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(camm PUBLIC Threads::Threads)
target_compile_options(camm PRIVATE -Wall -Wextra -Wpedantic)
add_executable(camm_demo src/main.cpp)
target_link_libraries(camm_demo PRIVATE camm)
enable_testing()
foreach(t store_test recovery_test compatibility_test concurrency_test benchmark_test)
 add_executable(${t} tests/${t}.cpp)
 target_link_libraries(${t} PRIVATE camm)
 add_test(NAME ${t} COMMAND ${t})
endforeach()
