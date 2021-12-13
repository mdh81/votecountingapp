#include "Command.h"
#include <string>
#include <vector>
#include "CommandCatalog.h"
using namespace std;

string HelpCommand::execute(const vector<string>& args) {
    if (args.size() > 1) { return getUsage(); }
    CommandCatalog& cmdCatalog = CommandCatalog::getInstance();
    string output;
    if (args.size() == 0) {
        output = "List of Available Commands: \n"; 
        for (auto& cmd : cmdCatalog.getAllCommands()) {
            output += cmd + "\t";
        }
    } else if (cmdCatalog.hasCommand(args.at(0))) {
        return cmdCatalog.getCommand(args.at(0)).getUsage();
    }
    return output;
}