#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool assignWorkers(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    std::vector<size_t>& shifts
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    	const size_t numWorkers = avail[0].size();
    const size_t numDays = avail.size();
    const size_t numShifts = dailyNeed * numDays;

    // check if it is possible to schedule the workers
    if (numShifts > numWorkers * maxShifts) {
        return false;
    }

    // initialize the schedule and shifts counters
    sched.clear();
    sched.resize(numDays, std::vector<Worker_T>(dailyNeed));
    std::vector<size_t> shifts(numWorkers, 0);

    // call the recursive algorithm
    return assignWorkers(avail, dailyNeed, maxShifts, sched, 0, shifts);
}

bool assignWorkers(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    std::vector<size_t>& shifts
) {
    const size_t numWorkers = avail[0].size();
    const size_t numDays = avail.size();

    // base case: we have scheduled d workers for each day
    if (day == numDays) {
        return true;
    }

    // try to assign a worker for this day
    for (size_t w = 0; w < numWorkers; w++) {
        if (avail[day][w] && shifts[w] < maxShifts) {
            // worker w is available on this day and has not worked m shifts
            sched[day].push_back(w);
            shifts[w]++;

            // recursive call on the next day
            if (assignWorkers(avail, dailyNeed, maxShifts, sched, day+1, shifts)) {
                return true;
            }

            // undo the assignment and try the next available worker
            sched[day].pop_back();
            shifts[w]--;
        }
    }

    // backtrack to the previous day
    return false;
}

