// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

/*
=======================================================================================
APPROACH 1: Chronological Sweep (Two Arrays / Two Pointers)
=======================================================================================
Explanation:
- We split the intervals into two independent arrays: `starts` and `ends`.
- We sort both chronologically.
- We use a pointer for `starts` and a pointer for `ends`.
- If the next `start` happens before the next `end`, a new meeting has begun before 
  any old meeting finished. We MUST rent a new room.
- If the next `start` happens on or after the next `end`, an old meeting finished. 
  We free up a room and move the `end` pointer forward.
=======================================================================================
*/

class Solution1 {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if (n == 0) return 0;
        
        vii starts, ends;
        for (auto& interval : intervals) {
            starts.pb(interval.start);
            ends.pb(interval.end);
        }
        
        sort(all(starts));
        sort(all(ends));
        
        int s_ptr = 0, e_ptr = 0;
        int active_rooms = 0;
        int max_rooms = 0;
        
        while (s_ptr < n) {
            
            // A meeting starts before the earliest ending meeting finishes
            if (starts[s_ptr] < ends[e_ptr]) {
                active_rooms++;
                max_rooms = max(max_rooms, active_rooms);
                s_ptr++;
            } 
            // A meeting finishes, freeing up a room for the taking!
            // Notice this also handles exactly equal times perfectly.
            else {
                active_rooms--;
                e_ptr++;
            }
        }
        
        return max_rooms;
    }
};

/*
=======================================================================================
APPROACH 2: Min-Heap (Simulating the Rooms)
=======================================================================================
Explanation:
- We sort the meetings by start time normally.
- We use a Priority Queue (Min-Heap) to track the END times of all currently active rooms.
- The top of the heap is ALWAYS the room that will finish the earliest.
- When evaluating a new meeting:
    - If its start time is >= the top of the heap, the earliest room is free! 
      We pop the old end time out.
    - We push the new meeting's end time into the heap.
- The size of the heap represents the number of rooms currently in use.
=======================================================================================
*/

class Solution2 {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int n = intervals.size();
        if (n == 0) return 0;
        
        // Sort chronologically by start time
        auto cmp = [&](const Interval& a, const Interval& b) -> bool {
            return a.start < b.start;
        };
        sort(all(intervals), cmp);
        
        // Min-Heap to track the end times of active meetings
        priority_queue<int, vector<int>, greater<int>> min_heap;
        
        for (int i = 0; i < n; i++) {
            
            // If the heap isn't empty, and the earliest ending meeting finished 
            // before or right when our new meeting starts, we can reuse that room!
            if (!min_heap.empty() && intervals[i].start >= min_heap.top()) {
                min_heap.pop(); // Remove the old meeting, room is cleared
            }
            
            // Occupy the room (either a brand new one, or the one we just cleared)
            min_heap.push(intervals[i].end);
        }
        
        // The heap contains exactly the number of concurrent rooms required
        return min_heap.size();
    }
};

// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

/*
=======================================================================================
PATTERN: Sweep Line (Single Sorted Event Array)
Time Complexity: O(N log N) | Space Complexity: O(N)
=======================================================================================
Explanation:
- We decompose every interval into two separate events: a Start ('S') and an End ('E').
- We push all 2N events into a single array of pairs and sort it.
- The default pair sort handles chronological ordering perfectly.
- Crucially, if times tie, 'E' (ASCII 69) comes before 'S' (ASCII 83), ensuring we 
  free up a room before trying to allocate a new one.
- We walk down the timeline, adding a room on 'S' and subtracting on 'E'.
=======================================================================================
*/

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        
        // Array to hold our timeline of events
        vector<pair<int, char>> events;
        
        // Deconstruct the intervals into independent events
        for (auto& interval : intervals) {
            events.pb({interval.start, 'S'}); // Group walks into the building
            events.pb({interval.end, 'E'});   // Group walks out of the building
        }
        
        // Sort chronologically. 
        // Ties are broken by character: 'E' comes before 'S', freeing rooms first!
        sort(all(events));
        
        int active_rooms = 0;
        int max_rooms = 0;
        
        // Walk the timeline
        for (auto& event : events) {
            
            if (event.second == 'S') {
                active_rooms++; // We need to open a room
            } else {
                active_rooms--; // A room was just freed
            }
            
            // Record the maximum concurrent rooms open at any given second
            max_rooms = max(max_rooms, active_rooms);
        }
        
        return max_rooms;
    }
};