#include "CommandCatalog.h"
using namespace std;

void CommandCatalog::initialize(const std::string& commandFileName) {

}

Command& CommandCatalog::getCommand(const string& commandName) { 

    //TODO: Temp code to get it to build
    m_commandsMap.try_emplace("Foo");
    return *m_commandsMap["Foo"].get();
}