#include "Command.h"
#include "ParserCollection.h"
#include "CommandsFileParser.h"
#include <string>
using namespace std;

string LoadCandidatesCommand::execute(const vector<string>& arguments) {
    if (arguments.size() != 1) {
        return getUsage();
    }
    string output;
    CommandsFileParser& cmdFileParser = ParserCollection::getInstance().getCommandsFileParser();
    cmdFileParser.parseFile(arguments.at(0));
    output += "File Loaded Successfully";
    return output;
}