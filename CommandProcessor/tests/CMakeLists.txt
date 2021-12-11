# test executables
add_executable(commandcatalog_test CommandCatalog_gt.cpp)
target_link_libraries(commandcatalog_test gtest_main parser commandprocessor)

add_executable(commandprocessor_test CommandProcessor_gt.cpp)
target_link_libraries(commandprocessor_test gtest_main parser commandprocessor)

# include path for service's headers
include_directories("../")

# enable gtest discovery
include(GoogleTest)
gtest_discover_tests(commandcatalog_test)
gtest_discover_tests(commandprocessor_test)