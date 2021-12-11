#include "gtest/gtest.h"
#include "CommandProcessor.h"
#include <fstream>
using namespace std;

TEST(CommandProcessor, TestSingleton) {
    CommandProcessor& cmdProc_1 = CommandProcessor::getInstance();
    CommandProcessor& cmdProc_2 = CommandProcessor::getInstance();
    ASSERT_EQ(&cmdProc_1, &cmdProc_2) << "Multiple instances of a singleton!";
}

/*TEST(CommandCatalog, TestInitialize) {
    CommandCatalog& catalog = CommandCatalog::getInstance();
    // Test loading invalid commands
    ofstream ofs("unsupportedcommands.txt");
    ofs << "nonExistentCommand" << endl;
    ofs.close();
    EXPECT_THROW({
        try {
            catalog.initialize("unsupportedcommands.txt");
        } catch (std::runtime_error& ex) {
            EXPECT_STREQ("Command 'nonExistentCommand' does not have an implementation", ex.what());
            throw;
        }
    }, std::runtime_error);

    // Test loading valid commands
    ofstream ofs_1;
    ofs_1.open("supportedcommands.txt");
    ofs_1 << "load\nresults\nlist\ntally\nhelp\n";
    ofs_1.close();
    EXPECT_NO_THROW({
        catalog.initialize("supportedcommands.txt");
    }) << "Exception thrown unexpectedly!";
}

TEST(CommandCatalog, TestGetCommand) {
    CommandCatalog& catalog = CommandCatalog::getInstance();
    ofstream ofs;
    ofs.open("supportedcommands.txt");
    ofs << "load\nresults\nlist\ntally\nhelp\n";
    ofs.close();
    catalog.initialize("supportedcommands.txt");
    EXPECT_NO_THROW({
        Command& cmd = catalog.getCommand("load");
    }) << "Exception thrown unexpectedly!";
    EXPECT_THROW({
        try {
            Command& cmd = catalog.getCommand("foo");
        } catch (std::runtime_error& ex) {
            EXPECT_STREQ("foo is not a valid command", ex.what());
            throw;
        }
    }, std::runtime_error) << "Exception was not thrown for an invalid command!";
}*/