#include "gtest/gtest.h"
#include "Command.h"
#include <fstream>
using namespace std;

class LoadCandidatesCommandTest : public testing::Test {
    protected:
    void SetUp() override {
        ofstream ofs("candidates.txt");
        ofs << "Candidate 1\nCandidate 2\nCandidate 3";
        ofs.close();
    }

};

TEST_F(LoadCandidatesCommandTest, TestInvalidArguments) {
    LoadCandidatesCommand cmd;
    ASSERT_EQ(cmd.execute({}), cmd.getUsage()) << "Expected a usage error when no argument is specified!";
    ASSERT_EQ(cmd.execute({"candidates.txt", "redundant arg"}), cmd.getUsage()) << "Expected a usage error when more than one argument is specified!";
}

TEST_F(LoadCandidatesCommandTest, TestLoadFile) {
    LoadCandidatesCommand cmd;
    ASSERT_STREQ(cmd.execute({"candidates.txt"}).data(), "File Loaded Successfully") << "File load failed!";
}
