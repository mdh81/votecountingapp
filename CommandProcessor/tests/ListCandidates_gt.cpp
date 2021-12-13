#include "gtest/gtest.h"
#include "Command.h"
#include <fstream>
using namespace std;

TEST(ListCandidatesCommandTest, TestInvalidArguments) {
    ListCandidatesCommand cmd;
    ASSERT_EQ(cmd.execute({"bad arg"}), cmd.getUsage()) << "Expected a usage error when arguments specified!";
}

TEST(ListCandidatesCommandTest, TestListingBeforeLoading) {
    ListCandidatesCommand cmd;
    ASSERT_EQ(cmd.execute({}), "Candidates list is empty\n") << "Expected a usage error when arguments specified!";
}

TEST(ListCandidatesCommandTest, TestListContents) {
    ofstream ofs("candidates.txt");
    ofs << "Candidate 1\nCandidate 2\nCandidate 3";
    ofs.close();
    LoadCandidatesCommand loadCmd;
    loadCmd.execute({"candidates.txt"});
    ListCandidatesCommand listCmd;
    ASSERT_STREQ(listCmd.execute({}).data(), "A.\tCandidate 1\nB.\tCandidate 2\nC.\tCandidate 3") << "Invalid candidates list";
}
