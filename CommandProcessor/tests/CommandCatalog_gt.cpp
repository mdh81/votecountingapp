#include "gtest/gtest.h"
#include "CommandCatalog.h"
using namespace std;

TEST(CommandCatalog, TestSingleton) {
    CommandCatalog& catalog_1 = CommandCatalog::getInstance();
    CommandCatalog& catalog_2 = CommandCatalog::getInstance();
    ASSERT_EQ(&catalog_1, &catalog_2) << "Multiple instances of a singleton!";
}