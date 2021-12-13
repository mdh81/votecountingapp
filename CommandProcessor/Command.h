#ifndef VCAPP_COMMANDS_H
#define VCAPP_COMMANDS_H

#include <string>

class Command {
    public:
        virtual std::string execute(const std::vector<std::string>& arguments) = 0;
        virtual std::string getUsage() = 0; 
    public:
        virtual ~Command() = default;
};

class ListCandidatesCommand : public Command {
    public:
        ListCandidatesCommand() = default; 
        std::string execute(const std::vector<std::string>& arguments) override;
        std::string getUsage() override { return "list: Lists candidate names with a prefix. Prefix is to be used for voting"; }
};

class LoadCandidatesCommand : public Command {
    public:
        LoadCandidatesCommand() = default;
        std::string execute(const std::vector<std::string>& arguments) override;
        std::string getUsage() override { return "load <Candidates File Name>: Load a file with candidate names"; }
};

class SubmitBallotCommand : public Command {
    public:
        SubmitBallotCommand() = default;
        std::string execute(const std::vector<std::string>& arguments) override;
        std::string getUsage() override { return "<Choice 1>...<Choice 3>"; }
};

class TallyCommand : public Command {
    public:
        TallyCommand() = default;
        std::string execute(const std::vector<std::string>& arguments) override;
        std::string getUsage() override { return "tally: Tallies ballots and determines the winner"; }
};

class ViewResultsCommand : public Command {
    public:
        ViewResultsCommand() = default;
        std::string execute(const std::vector<std::string>& arguments) override;
        std::string getUsage() override { return "results <candidate name>: Unimplemented"; }
};

class HelpCommand : public Command {
    public:
        std::string execute(const std::vector<std::string>& arguments) override;
        std::string getUsage() override { return "help [command name]"; }
};

#endif