add_library(
    commandprocessor
    LoadCandidatesCommand.cpp
    ListCandidatesCommand.cpp 
    SubmitBallotCommand.cpp 
    TallyCommand.cpp 
    ViewResultsCommand.cpp 
    CommandCatalog.cpp
    CommandProcessor.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/Parser/
    ${CMAKE_SOURCE_DIR}/VoteCounter)

add_subdirectory(tests)