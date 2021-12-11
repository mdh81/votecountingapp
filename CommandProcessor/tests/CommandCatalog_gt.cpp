#include "gtest/gtest.h"
#include "CommandCatalog.h"
#include <fstream>
using namespace std;

TEST(CommandCatalog, TestSingleton) {
    CommandCatalog& catalog_1 = CommandCatalog::getInstance();
    CommandCatalog& catalog_2 = CommandCatalog::getInstance();
    ASSERT_EQ(&catalog_1, &catalog_2) << "Multiple instances of a singleton!";
}

TEST(CommandCatalog, TestInitialize) {
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
    catalog.initialize("supportedcommands.txt");
}