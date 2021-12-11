#include "gtest/gtest.h"
#include "CandidatesFileParser.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

TEST(CandidatesParser, TestDefaultState) {
    ASSERT_EQ(CandidatesFileParser().getCandidates().size(), 0) << "Incorrect default state!"; 
}

TEST(CandidateParser, TestValidFileHandling) {
    CandidatesFileParser cparser;
    cparser.parseFile("candidates.txt");
    const vector<string>& candidatesList = cparser.getCandidates();
    ASSERT_EQ(candidatesList.size(), 5) << "Invalid number of candidates reported!";
    for (auto i = 1; i <= 3; ++i) {
        ASSERT_EQ(candidatesList[i-1], string("Candidate ") + to_string(i)) << "Incorrect candidate names!";
    }
    ASSERT_EQ(candidatesList[3], "4") << "Candidate with single character not read correctly!";
}

TEST(CandidateParser, TestEmptyFileHandling) {
    ofstream ofs("emptyfile.txt");
    ofs.close();
    CandidatesFileParser cparser;
    cparser.parseFile("emptyfile.txt");
    const vector<string>& candidatesList = cparser.getCandidates();
    ASSERT_EQ(candidatesList.size(), 0) << "Invalid number of candidates reported for empty file!";
}

TEST(CandidateParser, TestNonExistentFileHandling) {
    EXPECT_THROW({
        try {
            CandidatesFileParser().parseFile("nonexistent.txt");
        } catch (std::runtime_error& ex) {
            EXPECT_STREQ("Unable to open file nonexistent.txt", ex.what());
            throw;
        }
    }, std::runtime_error);
}