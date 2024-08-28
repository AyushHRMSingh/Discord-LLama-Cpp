# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(LLamaDppBot VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    /usr/local/include
)

# Specify the library directory path for dpp
link_directories(/usr/local/Cellar/libdpp/10.0.30/lib)

# Add the executable target
add_executable(LLamaDppBot src/bot.cpp)

# Link against the dpp library
target_link_libraries(LLamaDppBot dpp)
