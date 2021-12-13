#include "CommandProcessor.h"
#include <sstream>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "VoteCounter.h"
#include "Command.h"
using namespace std;

void CommandProcessor::initialize(const string& commandsFileName) {
    m_commandCatalog.initialize(commandsFileName);
}

void CommandProcessor::cmdLoop(istream& inputStream, ostream& outputStream) const {
    string cmdStr;
    outputStream << "vcapp > ";
    while (getline(inputStream, cmdStr)) {
        if (cmdStr == "exit") break;
        istringstream tokenizer(cmdStr);
        string cmdToken, cmdName;
        vector<string> cmdArgs;
        unsigned numTokens = 0;
        while(getline(tokenizer, cmdToken, ' ')) {
            if (numTokens == 0) cmdName = std::move(cmdToken);
            else cmdArgs.emplace_back(std::move(cmdToken));
            ++numTokens;
        }
        try {
            if (!cmdName.empty()) {
                // Handle case where attempts to submit a ballot. Could have relied on 
                // looking up the candidate name against catalog and handling InvalidCommandException.
                // But the issue is there could conceivably be a candidate with the same name as command
                // Second issue is relying on exception handling for a heavy traffic code path (each ballot submission)
                // could cause performance degradation
                if (VoteCounter::getInstance().hasCandidate(cmdName)) {
                    cmdArgs.insert(cmdArgs.begin(), cmdName);
                    SubmitBallotCommand().execute(cmdArgs);
                } else { 
                    // Handle case where user attempts to run a named command
                    Command& command = m_commandCatalog.getCommand(cmdName);
                    outputStream << command.execute(cmdArgs) << endl;
                }
            }
        } catch(InvalidCommandException& ex) {
            outputStream << "Invalid command. Try help" << endl;
        }
        outputStream << "vcapp > ";
    }
}