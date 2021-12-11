#ifndef VAPP_PARSER_H
#define VAPP_PARSER_H

#include <string>

class FileParser {
    public:
        void parseFile(const std::string& fileName);
    protected:
        std::string m_contents;
};

#endif