#include "Ballot.h"
#include "VoteCounter.h"
#include <iostream>
using namespace std;

Ballot::Ballot(const vector<Candidate*>& candidates) {
    m_preferredCandidates = candidates;
    m_exhausted = false;
    m_currentPreferredCandidate = m_preferredCandidates.empty() ? 
        nullptr : m_preferredCandidates.front();
}

// Return the first candidate in the preference order that has not been eliminated yet
Candidate* Ballot::evaluate() {
    if (!m_exhausted) {
        for (auto prefCandidate : m_preferredCandidates) {
            if (!prefCandidate->isEliminated()) {
                m_currentPreferredCandidate = prefCandidate;
                return prefCandidate;
            }
        }
    }
    // If all the preferred candidates were eliminated mark self as exhausted
    m_exhausted = true;
    return nullptr;
}