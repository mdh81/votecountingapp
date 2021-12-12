#ifndef VCAPP_VOTE_COUNTER_H
#define VCAPP_VOTE_COUNTER_H

#include "Candidate.h"
#include <vector>

class VoteCounter {
    public:
        static VoteCounter& getInstance() {
            static VoteCounter instance;
            return instance;
        }
        void setCandidates(std::vector<Candidate>& candidates);

    public:
        VoteCounter(VoteCounter&) = delete;
        VoteCounter(VoteCounter&&) = delete;
        VoteCounter& operator=(VoteCounter&) = delete;
        VoteCounter& operator=(VoteCounter&&) = delete;
    private:
        VoteCounter() = default; 

};


#endif