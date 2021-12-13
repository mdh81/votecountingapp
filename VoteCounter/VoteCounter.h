#ifndef VCAPP_VOTE_COUNTER_H
#define VCAPP_VOTE_COUNTER_H

#include "Candidate.h"
#include "Ballot.h"
#include <vector>
#include <unordered_map>
#include <memory>

class VoteCounter {
    public:
        static VoteCounter& getInstance() {
            static VoteCounter instance;
            return instance;
        }
        // Getters and setters for Candidates
        // NOTE: Assumes ownership of Candidate objects
        void setCandidates(Candidate::CandidateVector& candidates);
        // Get all registered candidates
        const Candidate::CandidateVector& getCandidates() const { return m_candidates; }
        // Get candidate with given prefix
        // NOTE: throws if there is no candidate with the given name
        const Candidate& getCandidate(const std::string& prefix) const; 
        // Pointer overload. Used to get pointers to the Candidate objects managed by this object 
        // The main use case is to get hold of Candidate objects to build Ballots
        std::vector<Candidate*> getCandidates(const std::vector<std::string>& prefixes);
        // No throw alternative that returns a boolean to indicate the presence of a candidate
        // with the given prefix
        bool hasCandidate(const std::string& prefix) const;

        // Getters and setters for Ballots
        // NOTE: Assumes ownership of the input Ballot object
        void addBallot(std::unique_ptr<Ballot>&& ballot) { m_ballots.push_back(std::move(ballot)); }
        const Ballot::BallotVector& getBallots() const { return m_ballots; }

        // Clears the state
        void reset() { m_ballots.clear(); m_candidates.clear(); m_candidatePrefixMap.clear(); }

        // Counts votes and declares a winner 
        void tally(std::string& results);

    // Usage control methods
    public:
        // Copy and move not allowed to enforce single instance
        VoteCounter(VoteCounter&) = delete;
        VoteCounter(VoteCounter&&) = delete;
        // Assignments are invalid
        VoteCounter& operator=(VoteCounter&) = delete;
        VoteCounter& operator=(VoteCounter&&) = delete;
    private:
        VoteCounter() = default; 

    // Internal implementation methods 
    private:
        bool executeCountingRound(std::vector<Candidate*>& candidatesInContention, std::string& roundResults);
        std::vector<Ballot*> getNonExhaustedBallots();
    
    private:
        Candidate::CandidateVector m_candidates;
        Ballot::BallotVector m_ballots;
        using CandidatePrefixMap = std::unordered_map<std::string, Candidate*>;
        CandidatePrefixMap m_candidatePrefixMap;
};


#endif