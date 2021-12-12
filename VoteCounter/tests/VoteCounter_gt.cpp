#include "gtest/gtest.h"
#include "Candidate.h"
#include "VoteCounter.h"
using namespace std;

TEST(VoteCounterTest, TestSetCandidates) {
    Candidate candidateA("Candidate 1", "A");
    Candidate candidateB("Candidate 2", "B");
    VoteCounter& vc = VoteCounter::getInstance(); 
    vector<Candidate> candidateVector;
}
