#include "VoteCounter.h"
#include "Exceptions.h"
using namespace std;

void VoteCounter::setCandidates(vector<Candidate>&& candidates) {
    m_candidates.reserve(candidates.size());
    for (auto& candidate : candidates) {
        m_candidates.push_back(std::move(candidate));
        m_candidatePrefixMap.emplace(m_candidates.back().getPrefix(), std::prev(m_candidates.end()));
    }
}

const Candidate& VoteCounter::getCandidate(const std::string& prefix) const {
   auto itr = m_candidatePrefixMap.find(prefix);
   if (itr == m_candidatePrefixMap.end()) throw InvalidCandidateException(prefix + " is not a valid candidate"); 
   return itr->second.operator*();
}