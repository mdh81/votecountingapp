#include "gtest/gtest.h"
#include "Candidate.h"
#include "VoteCounter.h"
#include "Exceptions.h"
#include <memory>
using namespace std;

TEST(VoteCounterTest, TestSetGetCandidates) {
    VoteCounter& vc = vc.getInstance();
    vc.reset();
    Candidate::CandidateVector candidateVector;
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 1", "A"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 3", "C"));
    vc.setCandidates(candidateVector);
    ASSERT_EQ(3, VoteCounter::getInstance().getCandidates().size()) << "Invalid number of candidates";
    ASSERT_STREQ("Candidate 3", VoteCounter::getInstance().getCandidates()[2]->getName().data()) << "Candidate list is incorrect";
}

TEST(VoteCounterTest, TestGetCandidate) {
    VoteCounter& vc = VoteCounter::getInstance();
    vc.reset();
    Candidate::CandidateVector candidateVector;
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 1", "A"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 3", "C"));
    vc.setCandidates(candidateVector);

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

TEST(VoteCounterTest, TestTally) {
    VoteCounter& vc = VoteCounter::getInstance();
    vc.reset();

    // 2 Candidates and 1 Ballot. One round is necessary to pick the winner which will be A
    Candidate::CandidateVector candidateVector;
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 1", "A"));;
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    vc.setCandidates(candidateVector);
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"A", "B"})));
    std::string results;
    vc.tally(results);
    ASSERT_TRUE(results.find("Candidate A met the quota") != string::npos) << "Incorrect state for A";
    ASSERT_TRUE(results.find("Winner is A") != string::npos) << "Failed to detect winner is A";
    vc.reset();
    results.clear();
    
    // 2 Candidates, 2 Ballots, Candidates tied in round 1, pick a random winner
    candidateVector.clear();
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 1", "A"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    vc.setCandidates(candidateVector);
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"A", "B"})));
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"B", "A"})));
    vc.tally(results);
    ASSERT_TRUE(results.find("Executing Round 2") == string::npos) << "Round 2 was unexpected";
    ASSERT_TRUE(results.find("is the only candidate remaining") != string::npos) << "Result is incorrect";
    vc.reset();
}

TEST(VoteCounterTest, TestTallyMultipleRounds) {
    VoteCounter& vc = VoteCounter::getInstance();
    vc.reset();

    // In this scenario, C and D don't have any first preference
    // ballots, they will be eliminated in round 1. Because, the non-exhausted
    // ballots can contain a second preference for either C or D, round 2 will
    // excute, but because the first preference candidates A and B are still 
    // in contention, they will get the ballots reassinged leaving C or D that
    // survived from the last round to be eliminated. Since A and B don't meet
    // the quota yet, round 3 will happen and either one of A or B will be eliminated 
    Candidate::CandidateVector candidateVector;
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 1", "A"));;
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 2", "B"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 3", "C"));
    candidateVector.push_back(std::make_unique<Candidate>("Candidate 3", "D"));
    vc.setCandidates(candidateVector);
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"A", "B"})));
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"B", "C"})));
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"A", "D"})));
    vc.addBallot(std::make_unique<Ballot>(vc.getCandidates({"B", "D"})));
    std::string results;
    vc.tally(results);

    // Assert that there are three rounds
    ASSERT_TRUE(results.find("Executing Round 1") != string::npos) << "Round 1 missing";
    ASSERT_TRUE(results.find("Executing Round 2") != string::npos) << "Round 2 missing";
    ASSERT_TRUE(results.find("Executing Round 3") != string::npos) << "Round 3 missing";

    // Assert that the winner is A or B
    ASSERT_TRUE(results.find("A is the only candidate remaining") != string::npos ||
                results.find("B is the only candidate remaining") != string::npos) << "Incorrect winner";

    vc.reset();
}
