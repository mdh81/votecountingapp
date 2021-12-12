#include "gtest/gtest.h"
#include "Candidate.h"
#include "Ballot.h"
#include "Types.h"
using namespace std;

// A ballot will be created such that the candidates listed on the ballot will be
// references into the list of Candidate objects maintained by the VoteCounter.
// Referencing is via iterators. This test ensures that these references are working
// as expected
TEST(BallotTest, TestGetCandidates) {
    VCTypes::CandidateVector candidates;
    candidates.emplace_back("Candidate 1", "A");
    candidates.emplace_back("Candidate 2", "B");
    candidates.emplace_back("Candidate 3", "C");
    VCTypes::CandidateReference itr = candidates.begin();
    VCTypes::CandidateReferences crefs { itr, itr + 1, itr + 2};
    Ballot ballot(crefs);
    // Assert that ballot's list of candidates are the instances that were passed in
    const VCTypes::CandidateReferences& candidatesOnBallot = ballot.getCandidates();
    ASSERT_EQ(&candidatesOnBallot.at(0).operator*(), &itr.operator*()) << "Invalid candidates on the ballot";
}

TEST(BallotTest, TestExhausted) {
    Ballot ballot({});
    ASSERT_FALSE(ballot.isExhausted()) << "Ballot wrongly marked exhausted";
    ballot.setExhausted();
    ASSERT_TRUE(ballot.isExhausted()) << "Ballot not marked exhausted";
}
