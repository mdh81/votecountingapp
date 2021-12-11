add_library(
    commandprocessor
    LoadCandidatesCommand.cpp
    ListCandidatesCommand.cpp 
    SubmitBallotCommand.cpp 
    TallyCommand.cpp 
    ViewResultsCommand.cpp 
    CommandCatalog.cpp
    CommandProcessor.cpp)

include_directories("../Parser/")

add_subdirectory(tests)