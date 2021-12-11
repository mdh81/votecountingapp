#include "CommandProcessor.h"
using namespace std;

void CommandProcessor::initialize(const string& commandsFileName) {
    m_commandCatalog.initialize(commandsFileName);
}