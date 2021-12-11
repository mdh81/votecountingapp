add_library(
    parser
    FileParser.cpp
    CandidatesFileParser.cpp
    CommandsFileParser.cpp)

add_subdirectory(tests)