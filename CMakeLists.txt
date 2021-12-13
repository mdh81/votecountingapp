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
add_subdirectory(VoteCounter)

add_executable(votecountingapp main.cpp driver.cpp) 
target_link_libraries(votecountingapp parser commandprocessor votecounter)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/CommandProcessor
)