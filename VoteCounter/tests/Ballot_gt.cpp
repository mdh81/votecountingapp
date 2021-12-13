#include "gtest/gtest.h"
#include "Candidate.h"
#include "VoteCounter.h"
#include "Ballot.h"
using namespace std;

// A ballot will be created such that the candidates listed on the ballot will be
// references into the list of Candidate objects maintained by the VoteCounter.
// Referencing is via iterators. This test ensures that these references are working
// as expected
TEST(BallotTest, TestGetCandidates) {
    Candidate::CandidateVector candidates;
    candidates.push_back(std::make_unique<Candidate>("Candidate 1", "A"));
    candidates.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    candidates.push_back(std::make_unique<Candidate>("Candidate 3", "C"));
    VoteCounter& vc = VoteCounter::getInstance();
    // save candidate name, the vector gets moved and its contents are not ready for use
    // in assertions
    auto firstStr = candidates.at(0)->getPrefix();
    vc.setCandidates(candidates);
    Ballot ballot(vc.getCandidates({"A", "B", "C"}));
    // Assert that ballot's list of candidates are the instances that were passed in
    vector<Candidate*> candidatesOnBallot = ballot.getPreferredCandidates();
    ASSERT_EQ(candidatesOnBallot.at(0)->getPrefix(), firstStr) << "Invalid candidates on the ballot";
}

TEST(BallotTest, TestExhausted) {
    Ballot ballot({});
    ASSERT_FALSE(ballot.isExhausted()) << "Ballot wrongly marked exhausted";
    ballot.setExhausted();
    ASSERT_TRUE(ballot.isExhausted()) << "Ballot not marked exhausted";
}

TEST(BallotTest, TestCurrentPreferredCandidate) {
    Candidate::CandidateVector candidates;
    candidates.push_back(std::make_unique<Candidate>("Candidate 1", "A"));
    candidates.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    VoteCounter& vc = VoteCounter::getInstance();
    vc.setCandidates(candidates);
    Ballot ballot(vc.getCandidates({"A", "B"}));
    ASSERT_STREQ(ballot.getPreferredCandidate()->getPrefix().data(), "A");
    ballot.getPreferredCandidate()->setEliminated();
    ballot.evaluate();
    ASSERT_STREQ(ballot.getPreferredCandidate()->getPrefix().data(), "B");
}
