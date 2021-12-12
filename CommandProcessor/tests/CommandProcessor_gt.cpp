#include "gtest/gtest.h"
#include "CommandProcessor.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
using namespace std;

TEST(CommandProcessor, TestCommandLoopStartAndEnd) {
    // Assert the command loop blocks until the "exit" command is typed
    // NOTE: Assertion is implicit because if the command loop doesn't exit the test
    // will timeout
    istringstream testStream;
    auto cmdLoop = [&testStream]() {
        CommandProcessor& cmdProc = CommandProcessor::getInstance();
        cmdProc.cmdLoop(testStream);
    };
    thread cmdThread(cmdLoop); 
    this_thread::sleep_for(chrono::seconds(1)); 
    string cmd = "exit\n";
    testStream >> cmd;
    cmdThread.join();
}

TEST(CommandProcessor, TestInvalidCommand) {
    // Assert the command loop gracefully handles invalid commands and stays in the loop
    // until exit is entered 
    istringstream inputStream("invalid_command");
    ostringstream outputStream;
    auto cmdLoop = [&inputStream, &outputStream]() {
        CommandProcessor& cmdProc = CommandProcessor::getInstance();
        cmdProc.cmdLoop(inputStream, outputStream);
    };
    thread cmdThread(cmdLoop);
    this_thread::sleep_for(chrono::seconds(1)); 

    // Check the message in the output stream and assert that a invalid command exception message is present
    ASSERT_TRUE(outputStream.str().find("Invalid command. Try help") != string::npos) << "Unexpected output for an invalid command";

    // Send exit command. Otherwise the test will timeout 
    string cmd = "exit\n";
    inputStream >> cmd;
    cmdThread.join();
}

TEST(CommandProcessor, TestSingleton) {
    CommandProcessor& cmdProc_1 = CommandProcessor::getInstance();
    CommandProcessor& cmdProc_2 = CommandProcessor::getInstance();
    ASSERT_EQ(&cmdProc_1, &cmdProc_2) << "Multiple instances of a singleton!";
}

TEST(CommandProcessor, TestInitialize) {
    CommandProcessor& cmdProc = CommandProcessor::getInstance();
    // Test loading commands file 
    ofstream ofs;
    ofs.open("commands.txt");
    ofs << "load\nresults\nlist\ntally\nhelp\n";
    ofs.close();
    EXPECT_NO_THROW({
        cmdProc.initialize("commands.txt");
    }) << "Exception thrown unexpectedly!";
}