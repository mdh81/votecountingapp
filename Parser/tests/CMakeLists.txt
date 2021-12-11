# copy test files
configure_file("./candidates.txt"
 ${CMAKE_CURRENT_BINARY_DIR}
 COPYONLY
 )

# test executables
add_executable(candidatesparser_test CandidatesParser_gt.cpp)
target_link_libraries(candidatesparser_test gtest_main parser)

# include source files directly
include_directories("../")

# enable gtest discovery
include(GoogleTest)
gtest_discover_tests(candidatesparser_test)