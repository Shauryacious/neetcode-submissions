// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<random>
#include<string>
#include<functional>
#include<iomanip>
#include<limits>
#include<array>
#include<utility>
#include<iterator>
#include<cstring>

using namespace std;

// Define Constants & Macros
#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define pb push_back
#define ppb pop_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define pll pair<ll, ll>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define all(x) (x).begin(), (x).end()
#define INF 1e18
#define ff first
#define ss second

/*
=======================================================================================
PATTERN: Dual Min-Heap Simulation (with C++17 Structured Bindings)
Time Complexity: O(M log M + M log N) | Space Complexity: O(N)
Where M is the number of meetings and N is the number of rooms.
=======================================================================================
EXPLANATION OF LOGIC:
- We enforce a linear chronological timeline by sorting meetings by start time.
- `free_rooms` (Min-Heap) holds integers representing available room IDs. It inherently 
  surfaces the lowest ID room to the top.
- `occupied_rooms` (Min-Heap) holds pairs of {end_time, room_id}. It inherently 
  surfaces the room that will finish earliest.
- For every incoming meeting, we first free up any rooms that finished at or before 
  the meeting's start time, shifting them from `occupied_rooms` back to `free_rooms`.
- We then attempt to allocate a room. If a free room exists, it is assigned instantly. 
  If all rooms are occupied, we extract the absolute earliest finishing room from 
  `occupied_rooms` using structured binding, calculate the delayed finish time, and 
  re-insert it into the heap.
=======================================================================================
*/

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        
        // Sort meetings chronologically by their start times
        sort(all(meetings));
        
        // Min-Heap 1: Manages the pool of unused rooms, ordered by room ID
        priority_queue<int, vector<int>, greater<int>> free_rooms;
        for (int i = 0; i < n; i++) {
            free_rooms.push(i);
        }
        
        // Min-Heap 2: Manages ongoing meetings -> {end_time, room_id}
        // Ordered by earliest end time, ties broken by lowest room_id
        priority_queue<pll, vector<pll>, greater<pll>> occupied_rooms;
        
        vii meeting_count(n, 0);
        
        for (auto& meeting : meetings) {
            ll original_start = meeting[0];
            ll original_end = meeting[1];
            
            // Phase A: Reclaim rooms where the meeting has successfully concluded
            while (!occupied_rooms.empty() && occupied_rooms.top().ff <= original_start) {
                free_rooms.push(occupied_rooms.top().ss);
                occupied_rooms.pop();
            }
            
            // Phase B: Allocate a room to the incoming meeting
            if (!free_rooms.empty()) {
                // Optimal case: A free room is readily available
                int room_number = free_rooms.top();
                free_rooms.pop();
                
                occupied_rooms.push({original_end, room_number});
                meeting_count[room_number]++;
                
            } else {
                // Delay case: All rooms are occupied. Must wait for the earliest vacancy.
                // Using C++17 Structured Binding for clean extraction
                auto [earliest_end, room_number] = occupied_rooms.top();
                occupied_rooms.pop();
                
                // Calculate the new shifted timeline for the delayed meeting
                ll duration = original_end - original_start;
                ll delayed_end_time = earliest_end + duration;
                
                occupied_rooms.push({delayed_end_time, room_number});
                meeting_count[room_number]++;
            }
        }
        
        // Final Evaluation: Identify the room utilized the most times
        int max_meetings = -1;
        int best_room = -1;
        
        for (int i = 0; i < n; i++) {
            if (meeting_count[i] > max_meetings) {
                max_meetings = meeting_count[i];
                best_room = i;
            }
        }
        
        return best_room;
    }
};