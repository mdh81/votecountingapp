#include "gtest/gtest.h"
#include "Candidate.h"
#include "VoteCounter.h"
#include "Exceptions.h"
using namespace std;

TEST(VoteCounterTest, TestSetGetCandidates) {
    vector<Candidate> candidateVector;
    candidateVector.emplace_back("Candidate 1", "A");
    candidateVector.emplace_back("Candidate 2", "B");
    candidateVector.emplace_back("Candidate 3", "C");
    VoteCounter::getInstance().setCandidates(std::move(candidateVector));
    ASSERT_EQ(3, VoteCounter::getInstance().getCandidates().size()) << "Invalid number of candidates";
    ASSERT_STREQ("Candidate 3", VoteCounter::getInstance().getCandidates()[2].getName().data()) << "Candidate list is incorrect";
}

TEST(VoteCounterTest, TestGetCandidate) {
    vector<Candidate> candidateVector;
    candidateVector.emplace_back("Candidate 1", "A");
    candidateVector.emplace_back("Candidate 2", "B");
    candidateVector.emplace_back("Candidate 3", "C");
    VoteCounter& vc = VoteCounter::getInstance();
    vc.setCandidates(std::move(candidateVector));
    ASSERT_STREQ(vc.getCandidate("B").getName().data(), "Candidate 2") << "Invalid candidate for given prefix";
    ASSERT_THROW({
        try {
            vc.getCandidate("D");
        } catch (InvalidCandidateException& ex) {
            ASSERT_STREQ(ex.what(), "D is not a valid candidate");
            throw;
        }
    }, InvalidCandidateException);
}
