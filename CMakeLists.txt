cmake_minimum_required(VERSION 3.10)

project(votecountingapp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# get gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
FetchContent_MakeAvailable(googletest)

# enable test discovery
enable_testing()

# add service sub-directories
add_subdirectory(Parser)
add_subdirectory(CommandProcessor)

add_executable(votecountingapp main.cpp) 