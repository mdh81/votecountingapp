#include "VoteCounter.h"
using namespace std;

void VoteCounter::setCandidates(vector<Candidate>&& candidates) {
    m_candidates.reserve(candidates.size());
    for (auto& candidate : candidates) {
        m_candidates.push_back(std::move(candidate));
    }
}