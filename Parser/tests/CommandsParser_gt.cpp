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
            CommandsFileParser().getCommandArgument("foo");
        } catch (std::runtime_error& ex) {
            EXPECT_STREQ("Command 'foo' undefined", ex.what());
            throw;
        }
    }, std::runtime_error) << "Runtime exception for undefined command expected!";
}

TEST(CommandsFileParser, TestValidFileHandling) {
    CommandsFileParser cparser;
    cparser.parseFile("commands.txt");
    vector<string> commands = cparser.getCommands();
    ASSERT_EQ(commands.size(), 4) << "Incorrect number of commands!";
    ASSERT_TRUE(std::find(commands.begin(), commands.end(), "load") != commands.end()) << "Expected to find load command!";
    ASSERT_TRUE(std::find(commands.begin(), commands.end(), "results") != commands.end()) << "Expected results command!";
}

TEST(CommandsFileParser, TestCommandArguments) {
    CommandsFileParser cparser;
    cparser.parseFile("commands.txt");
    vector<string> commands = cparser.getCommands();
    ASSERT_EQ(cparser.getCommandArgument("load"), "<Candidates File>") << "Incorrect argument for load command!";
    ASSERT_EQ(cparser.getCommandArgument("results"), "<Candidate Name>") << "Incorrect argument for results command!";
    ASSERT_EQ(cparser.getCommandArgument("list"), "") << "Expected no arguments for list command!";
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