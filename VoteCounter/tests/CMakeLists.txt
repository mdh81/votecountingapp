# test executables
add_executable(candidate_test Candidate_gt.cpp)
target_link_libraries(candidate_test gtest_main votecounter)
add_executable(votecounter_test VoteCounter_gt.cpp)
target_link_libraries(votecounter_test gtest_main votecounter)


# include path for service's headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

# enable gtest discovery
include(GoogleTest)
gtest_discover_tests(candidate_test)