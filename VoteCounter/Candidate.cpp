#include "Candidate.h"
using namespace std;

Candidate::Candidate(const std::string& name, const std::string& prefix) : m_name(name), m_prefix(prefix) {
    m_rank = 0;
    m_eliminated = false;
    m_numBallots = 0;
}