#include "Driver.h"
#include <string>
#include "CommandProcessor.h"

void Driver::loadCommands(const std::string& commandFile) {
    CommandProcessor::getInstance().initialize(commandFile);
    CommandProcessor::getInstance().cmdLoop();
}

void Driver::loadCommandsAndCandidatesFile(const std::string& commandFile, const std::string& candidatesFile) {

}