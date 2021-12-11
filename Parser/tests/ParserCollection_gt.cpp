#include "gtest/gtest.h"
#include "ParserCollection.h"
#include "CandidatesFileParser.h"
#include "CommandsFileParser.h"
using namespace std;

TEST(ParserCollection, TestSingleton) {
    ParserCollection& parserCollection_1 = ParserCollection::getInstance();
    ParserCollection& parserCollection_2 = ParserCollection::getInstance();
    ASSERT_EQ(&parserCollection_1, &parserCollection_2) << "Multiple instances of a singleton!";
}