#include "gtest/gtest.h"
#include "CommandsFileParser.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

TEST(CommandsFileParser, TestDefaultState) {
    ASSERT_EQ(CommandsFileParser().getCommands().size(), 0) << "Incorrect default state!"; 
    EXPECT_THROW({
        try {
            CommandsFileParser().getCommandArguments("foo");
        } catch (std::runtime_error& ex) {
            EXPECT_STREQ("Command foo undefined", ex.what());
            throw;
        }
    }, std::runtime_error) << "Runtime exception for undefined command expected!";
}

TEST(CandidateParser, TestNonExistentFileHandling) {
    EXPECT_THROW({
        try {
            CommandsFileParser().parseFile("nonexistent.txt");
        } catch (std::runtime_error& ex) {
            EXPECT_STREQ("Unable to open file nonexistent.txt", ex.what());
            throw;
        }
    }, std::runtime_error) << "Runtime exception for nonexistent file expected!";
}