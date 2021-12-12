#include "gtest/gtest.h"
#include "Candidate.h"
#include "VoteCounter.h"
using namespace std;

TEST(VoteCounterTest, TestSetCandidates) {
    vector<Candidate> candidateVector;
    candidateVector.emplace_back("Candidate 1", "A");
    candidateVector.emplace_back("Candidate 2", "B");
    candidateVector.emplace_back("Candidate 3", "C");
    VoteCounter::getInstance().setCandidates(std::move(candidateVector));
    ASSERT_EQ(3, VoteCounter::getInstance().getCandidates().size()) << "Invalid number of candidates";
    ASSERT_STREQ("Candidate 3", VoteCounter::getInstance().getCandidates()[2].getName().data()) << "Candidate list is incorrect";
}
