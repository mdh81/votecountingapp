add_library(
    votecounter 
    VoteCounter.cpp
    Candidate.cpp
    Ballot.cpp
    )

add_subdirectory(tests)

install(TARGETS votecounter DESTINATION lib)