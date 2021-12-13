#include "gtest/gtest.h"
#include "Command.h"
#include "VoteCounter.h"
#include <fstream>
using namespace std;

class SubmitBallotCommandTest : public testing::Test {
    protected:
    void SetUp() override {
        VoteCounter::getInstance().reset();
        ofstream ofs("candidates.txt");
        ofs << "Candidate 1\nCandidate 2\nCandidate 3";
        ofs.close();
        LoadCandidatesCommand loadCmd;
        loadCmd.execute({"candidates.txt"});
    }
};

TEST_F(SubmitBallotCommandTest, TestValidSubmission) {
    SubmitBallotCommand cmd;
    cmd.execute({"A", "B", "C"});
    const Ballot::BallotVector& bv = VoteCounter::getInstance().getBallots();
    ASSERT_EQ(bv.size(), 1) << "Ballot not registered as expected";
    ASSERT_EQ(bv[0].getCandidates().size(), 3) << "Ballot does not have the right number of candidates";
    ASSERT_EQ(bv[0].getCandidates()[0]->getName(), "Candidate 1") << "Candidates on the ballot are not ordered correctly";
    ASSERT_EQ(bv[0].getCandidates()[1]->getName(), "Candidate 2") << "Candidates on the ballot are not ordered correctly";
    ASSERT_EQ(bv[0].getCandidates()[2]->getName(), "Candidate 3") << "Candidates on the ballot are not ordered correctly";
}

TEST_F(SubmitBallotCommandTest, TestInValidSubmission) {
    SubmitBallotCommand cmd;
    // Some invalid entries
    cmd.execute({"A", "B", "C", "A" /*duplicate*/, "Q" /*invalid*/});
    const Ballot::BallotVector& bv = VoteCounter::getInstance().getBallots();
    ASSERT_EQ(bv.size(), 1) << "Ballot not registered as expected";
    ASSERT_EQ(bv[0].getCandidates().size(), 3) << "Ballot does not have the right number of candidates";
    ASSERT_EQ(bv[0].getCandidates()[0]->getName(), "Candidate 1") << "Candidates on the ballot are not ordered correctly";
    ASSERT_EQ(bv[0].getCandidates()[1]->getName(), "Candidate 2") << "Candidates on the ballot are not ordered correctly";
    ASSERT_EQ(bv[0].getCandidates()[2]->getName(), "Candidate 3") << "Candidates on the ballot are not ordered correctly";
    // All invalid entries
    cmd.execute({"X", "Y", "Z"});
    ASSERT_EQ(bv.size(), 1) << "Invalid ballot not rejected";
}
