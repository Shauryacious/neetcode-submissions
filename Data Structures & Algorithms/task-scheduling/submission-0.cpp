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
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define py cout<<"YES"<<nl
#define pn cout<<"NO"<<nl
#define pm cout<<"-1"<<nl

// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<pll> vpll;

#define vvpll vector<vpll>


/*
=======================================================================================
APPROACH: Greedy Math Formula
Time Complexity: O(N) | Space Complexity: O(1) auxiliary (size 26 array)
=======================================================================================
Intuition & Visualization:
- We count the frequencies of all tasks using an array of size 26.
- We find the highest frequency (`max_freq`).
- We count how many tasks share this exact highest frequency (`count_max_freq`).
- We calculate the time required to schedule just these most frequent tasks, including 
  their mandatory cooldown gaps: 
  formula_time = (max_freq - 1) * (n + 1) + count_max_freq
- Finally, we return `max(tasks.size(), formula_time)`. If the formula gives a number 
  smaller than the total tasks, it means no idle time is needed at all!
=======================================================================================
*/
class Solution1 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vii freq(26, 0);
        int max_freq = 0;
        
        // 1. Calculate frequencies and find the absolute maximum frequency
        for (char task : tasks) {
            freq[task - 'A']++;
            max_freq = max(max_freq, freq[task - 'A']);
        }
        
        // 2. Count how many different tasks share this exact maximum frequency
        int count_max_freq = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] == max_freq) {
                count_max_freq++;
            }
        }
        
        // 3. Apply the mathematical formula
        int chunks = max_freq - 1;
        int chunk_length = n + 1;
        
        int formula_time = (chunks * chunk_length) + count_max_freq;
        
        // 4. Return the maximum of our calculated time or the raw number of tasks
        int total_tasks = tasks.size();
        return max(total_tasks, formula_time);
    }
};

/*
=======================================================================================
APPROACH 2: CPU Simulation (Descending Multiset + Cooldown Queue)
Time Complexity: O(Total CPU Cycles) | Space Complexity: O(1) auxiliary (max size 26)
=======================================================================================
Explanation:
- We use a `multiset<int, greater<int>>` to act perfectly as a Max-Heap. The task 
  with the highest remaining frequency sits exactly at `mst.begin()`.
- We use a `queue<pii>` to act as our cooldown waiting room. It stores pairs of 
  `{remaining_frequency, time_it_can_be_scheduled_again}`.
- In each unit of `time`, we:
  1. Extract the max element directly from `mst.begin()`. We decrement its frequency 
     and push it to the cooldown queue if it needs to run again.
  2. Check the front of the cooldown queue. If the required cooldown time has passed 
     (`wait_q.front().ss == time`), we take it out and re-insert it into our multiset.
- The loop ends when BOTH the multiset and the cooldown queue are entirely empty.
=======================================================================================
*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        
        // 1. Calculate frequencies
        vii freq(26, 0);
        for (char task : tasks) {
            freq[task - 'A']++;
        }
        
        // 2. Populate our "Max-Heap" using a descending multiset
        multiset<int, greater<int>> mst;
        for (int f : freq) {
            if (f > 0) {
                mst.insert(f);
            }
        }
        
        // Queue stores {remaining_frequency, available_time}
        queue<pii> wait_q;
        int time = 0;
        
        // Run the CPU clock until all tasks are fully processed
        while (!mst.empty() || !wait_q.empty()) {
            time++; // Tick the clock
            
            // If there are available tasks to process
            if (!mst.empty()) {
                
                // Extract the highest frequency task natively from the front
                int curr_freq = *mst.begin();
                mst.erase(mst.begin());
                
                // Execute the task
                curr_freq--;
                
                // If it still needs to be run again, put it in timeout!
                if (curr_freq > 0) {
                    wait_q.push({curr_freq, time + n});
                }
            }
            
            // Check if the task waiting the longest is ready to leave timeout
            if (!wait_q.empty() && wait_q.front().ss == time) {
                
                // Re-insert its remaining frequency back into our multiset
                mst.insert(wait_q.front().ff);
                wait_q.pop();
            }
        }
        
        return time;
    }
};