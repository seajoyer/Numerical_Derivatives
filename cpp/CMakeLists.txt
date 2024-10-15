cmake_minimum_required(VERSION 3.10)
project(NumericalDerivatives VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(numerical_derivatives
    src/derivatives.cpp
    src/utils.cpp
    src/plotting.cpp
)

add_executable(numerical_derivatives_example examples/main.cpp)
target_link_libraries(numerical_derivatives_example numerical_derivatives)

install(TARGETS numerical_derivatives DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
