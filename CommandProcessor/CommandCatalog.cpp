#include "CommandCatalog.h"
#include "ParserCollection.h"
#include "CommandsFileParser.h"
#include <iostream>
using namespace std;

void CommandCatalog::initialize(const std::string& commandsFileName) {
    CommandsFileParser& cmdParser = ParserCollection::getInstance().getCommandsFileParser();
    cmdParser.parseFile(commandsFileName);
    auto cmds = cmdParser.getCommands();
    for (auto& cmd : cmds) {
        if (cmd == "load") {
            m_commandsMap.try_emplace(cmd, new LoadCandidatesCommand());
        } else if (cmd == "results") {
            m_commandsMap.try_emplace(cmd, new ViewResultsCommand());
        } else if (cmd == "list") {
            m_commandsMap.try_emplace(cmd, new ListCandidatesCommand());
        } else if (cmd == "tally") {
            m_commandsMap.try_emplace(cmd, new TallyCommand());
        } else if (cmd == "help") {
            m_commandsMap.try_emplace(cmd, nullptr); // TODO: Implement help command
        } else {
            cerr << cmd << endl;
            throw std::runtime_error("Command '" + cmd + "' does not have an implementation");
        }
    }
}

Command& CommandCatalog::getCommand(const string& commandName) { 

    //TODO: Temp code to get it to build
    m_commandsMap.try_emplace("Foo");
    return *m_commandsMap["Foo"].get();
}