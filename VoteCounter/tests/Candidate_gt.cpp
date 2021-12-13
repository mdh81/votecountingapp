#include "gtest/gtest.h"
#include "Candidate.h"
using namespace std;

TEST(CandidateTest, TestSetterGetter) {
    Candidate candidate("Candidate 1", "A");
    ASSERT_EQ(candidate.getName(), "Candidate 1") << "getName() failed";
    ASSERT_EQ(candidate.getPrefix(), "A") << "getPrefix() failed";
    ASSERT_EQ(candidate.isEliminated(), false) << "invalid initial value for eliminated";
    candidate.setEliminated();
    ASSERT_EQ(candidate.isEliminated(), true) << "isEliminated() failed";
}
