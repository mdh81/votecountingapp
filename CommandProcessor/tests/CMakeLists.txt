# test executables
add_executable(commandcatalog_test CommandCatalog_gt.cpp)
target_link_libraries(commandcatalog_test gtest_main parser commandprocessor)

# include path for service's headers
include_directories("../")

# enable gtest discovery
include(GoogleTest)
gtest_discover_tests(commandcatalog_test)