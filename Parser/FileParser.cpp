#include "FileParser.h"
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

void FileParser::parseFile(const string& fileName) {
    if (!m_contents.empty()) m_contents.clear();
    ifstream ifs(fileName);
    if (!ifs) throw std::runtime_error("Unable to open file " + fileName);
    ifs.seekg(0, ios::end);
    auto fileSize = ifs.tellg();
    m_contents.resize(fileSize);
    ifs.seekg(0);
    ifs.read(m_contents.data(), fileSize);
}