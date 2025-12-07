cmake_minimum_required(VERSION 3.15)
project(svd_bindings)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_svd_core 
    python/bindings.cpp
    src/svd.cpp
)

target_include_directories(_svd_core PRIVATE src/)

install(TARGETS _svd_core DESTINATION .)
