#include "CommandProcessor.h"
#include <sstream>
#include <string>
#include <vector>
#include "Exceptions.h"
using namespace std;

void CommandProcessor::initialize(const string& commandsFileName) {
    m_commandCatalog.initialize(commandsFileName);
}

void CommandProcessor::cmdLoop(istream& inputStream, ostream& outputStream) const {
    string cmdStr;
    outputStream << "vcapp > ";
    while (getline(inputStream, cmdStr)) {
        if (cmdStr == "exit") break;
        try {
            istringstream tokenizer(cmdStr);
            string cmdToken, cmdName;
            vector<string> cmdArgs;
            unsigned numTokens = 0;
            while(getline(tokenizer, cmdToken, ' ')) {
                if (numTokens == 0) cmdName = std::move(cmdToken);
                else cmdArgs.emplace_back(std::move(cmdToken));
                ++numTokens;
            }
            Command& command = m_commandCatalog.getCommand(cmdName);
        } catch(InvalidCommandException& ex) {
            outputStream << "Invalid command. Try help" << endl;
        }
        outputStream << "vcapp > ";
    }
}