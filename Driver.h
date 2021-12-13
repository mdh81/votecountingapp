#ifndef VCAPP_DRIVER_H
#define VCAPP_DRIVER_H
#include <string>
class Driver {
    public:
        void loadCommands(const std::string& commandFile);
        void loadCommandsAndCandidatesFile(const std::string& commandFile, const std::string& candidatesFile);
};
#endif