#include "VoteCounter.h"
#include "Ballot.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <random>
using namespace std;

namespace {
    size_t GetRandomInRange(size_t start, size_t end) {
        uniform_int_distribution<> dist(start, end);
        std::random_device rd;
        std::mt19937 gen(rd());
        return dist(gen);
    }
}

void VoteCounter::setCandidates(Candidate::CandidateVector& candidates) {
    m_candidates.reserve(candidates.size());
    for (auto& candidate : candidates) {
        m_candidates.push_back(std::move(candidate));
        m_candidatePrefixMap.emplace(m_candidates.back()->getPrefix(), m_candidates.back().get());
    }
}

const Candidate& VoteCounter::getCandidate(const std::string& prefix) const {
   auto itr = m_candidatePrefixMap.find(prefix);
   if (itr == m_candidatePrefixMap.end()) throw InvalidCandidateException(prefix + " is not a valid candidate"); 
   return *itr->second;
}

// Expect RVO to build this in caller's memory
vector<Candidate*> VoteCounter::getCandidates(const std::vector<std::string>& prefixes) {
   vector<Candidate*> candidates(prefixes.size());
   for (size_t i = 0; i < prefixes.size(); ++i) {
       auto itr = m_candidatePrefixMap.find(prefixes.at(i));
       if (itr == m_candidatePrefixMap.end()) candidates.at(i) = nullptr; 
       else candidates.at(i) = itr->second;
   }
   return candidates;
}

bool VoteCounter::hasCandidate(const std::string& prefix) const {
    auto itr = m_candidatePrefixMap.find(prefix);
    return m_candidatePrefixMap.find(prefix) != m_candidatePrefixMap.end();
}

void VoteCounter::tally(string& results) {
    unsigned roundNum = 0;
    string roundResults;
    bool winnerFound = false;
    
    // Initialize candidates in contention with the full list of candidates
    vector<Candidate*> candidatesInContention;
    candidatesInContention.reserve(m_candidates.size());
    for (auto itr = m_candidates.begin(), end = m_candidates.end(); itr != end; ++itr) {
        candidatesInContention.push_back((*itr).get());
    }
    
    do {
        results += "Executing Round " + to_string(++roundNum) + "\n";
        winnerFound = executeCountingRound(candidatesInContention, roundResults);
        results += roundResults;
        roundResults.clear();
    } while (!winnerFound);
}

bool VoteCounter::executeCountingRound(vector<Candidate*>& candidatesInContention, string& roundResults) {

    bool hasLowest = false;
    
    // Step 1: Get Non-exhausted Ballots
    vector<Ballot*> nonExhaustedBallots = getNonExhaustedBallots();

    // Step 2: Set Quota
    size_t quota = (nonExhaustedBallots.size() / 2) + 1;

    // Step 3: Assign ballots to candidates as per highest preference for this round
    // Store a reference to candidates that meet quota
    vector<const Candidate*> candidatesMeetingQuota;
    candidatesMeetingQuota.reserve(candidatesInContention.size());
    for (auto& ballotRef : nonExhaustedBallots) {
        auto preferredCandidate = ballotRef->getPreferredCandidate();
        preferredCandidate->assignBallot();
        if (preferredCandidate->getNumberOfAssignedBallots() >= quota) {
            candidatesMeetingQuota.push_back(preferredCandidate);
        }
    }
    candidatesMeetingQuota.shrink_to_fit();

    // Step 4: If multiple candidates meet the quota, we pick a random winner.
    // If no candidate meets the quota, we eliminate the lowest ranked candidate
    // and proceed to the next round. If there are more than one candidate with
    // the lowest rank, we randomly pick a candidate for elimination 
    if (!candidatesMeetingQuota.empty()) {
        roundResults += "Candidate";
        roundResults += (candidatesMeetingQuota.size() == 1 ? " " : "s ");
        for (auto e : candidatesMeetingQuota) {
            roundResults += e->getPrefix();
            roundResults += " ";
        }
        roundResults += "met the quota\n";

        size_t winnerIndex = candidatesMeetingQuota.size() == 1 ? 0 : GetRandomInRange(0, candidatesMeetingQuota.size() - 1);
        roundResults += "Winner is ";
        roundResults += candidatesMeetingQuota.at(winnerIndex)->getPrefix() + "\n";
        return true; 
    } else {
        roundResults += "None of the candidates met the quota. ";
        std::sort(candidatesInContention.begin(), candidatesInContention.end(),
                 [](Candidate* c1, Candidate* c2) { return c1->getNumberOfAssignedBallots() < c2->getNumberOfAssignedBallots(); });
        size_t lowestNumberOfBallots = candidatesInContention.front()->getNumberOfAssignedBallots();
        auto firstUniqueRank = std::find_if(candidatesInContention.begin(), candidatesInContention.end(),
                                          [lowestNumberOfBallots](Candidate* cref) {return cref->getNumberOfAssignedBallots() > lowestNumberOfBallots; });
        size_t randomIndex;
        if (firstUniqueRank == candidatesInContention.end()) {
            // All of them had the same rank
            randomIndex = GetRandomInRange(0, candidatesInContention.size() - 1);
        } else {
            // There was at least one item ranked higher than the duplicate lowest ranked entries. Check if there is only one lowest ranked item
            // that criteria changes our results message
            auto dist = std::distance(candidatesInContention.begin(), firstUniqueRank - 1);
            if ((hasLowest = (dist == 0))) randomIndex = 0;
            else randomIndex = GetRandomInRange(0, std::distance(candidatesInContention.begin(), firstUniqueRank - 1));
        }
        // Mark the chosen candidate as eliminated
        candidatesInContention.at(randomIndex)->setEliminated();
        roundResults += (hasLowest ? "Lowest ranked candidate " : "Randomly chosen candidate ") + candidatesInContention.at(randomIndex)->getPrefix() + " eliminated\n";
        candidatesInContention.erase(candidatesInContention.begin() + randomIndex); 

        // Step 5: If there is only candidate remaining, then declare them winner
        if (candidatesInContention.size() == 1) {
            roundResults += candidatesInContention.at(0)->getPrefix() + " is the only candidate remaining and is declared the winner\n";
            return true;
        } else {
            // Reset ballot assignments so to make sure the evaluation against quota is correct for subsequent rounds
            for_each(candidatesInContention.begin(), candidatesInContention.end(),
                    [](Candidate* candidate) { candidate->resetAssignment(); });
            return false;
        }
    }
}

vector<Ballot*> VoteCounter::getNonExhaustedBallots() {
    vector<Ballot*> nonExhausted;
    nonExhausted.reserve(m_ballots.size());
    for (auto itr = m_ballots.begin(), end = m_ballots.end(); itr != end; ++itr) {
        itr->get()->evaluate();
        Candidate* preferredCandidate = itr->get()->getPreferredCandidate();
        if (preferredCandidate != nullptr) nonExhausted.push_back(itr->get());
    }
    nonExhausted.shrink_to_fit();
    return nonExhausted;
}

void VoteCounter::clear() {
    m_ballots.clear();
    for_each(m_candidates.begin(), m_candidates.end(),
             [](unique_ptr<Candidate>& candidate) { candidate->resetAssignment(); candidate->resetEliminated();});
}