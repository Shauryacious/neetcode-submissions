// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>

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

/*
=======================================================================================
APPROACH 1: Top-Down Dynamic Programming (2D State - Take / Not Take)
Time Complexity: O(N^2) | Space Complexity: O(N^2)
=======================================================================================
Intuition:
- At each index `i`, we make a choice to either take or skip `a[i]`.
- We can only take `a[i]` if it is strictly greater than the last picked element.
- We track the index of the last picked element using `prev`.

Concept & State Definition:
- State: `f(i, prev)` -> returns the length of the longest increasing subsequence 
  from index `i` to the end, given the last picked element was at index `prev`.
- `dp[i][prev + offset]` caches the result. We use `offset = 1` because `prev` starts 
  at `-1`.

Base Case: 
- If `i == n`, we have evaluated all elements. Return 0.

Transition: 
- CASE 1 (`prev == -1`): Nothing picked yet. We can freely Take or Skip.
- CASE 2 (`prev != -1`): We have an active sequence. 
  - If `a[i] > a[prev]`, valid successor. We can Take or Skip.
  - If `a[i] <= a[prev]`, invalid successor. We MUST Skip.
=======================================================================================
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& a) {
        int n = a.size();
        
        // DP table: 2505 x 2505 initialized to -1.
        vvii dp(n + 5, vii(n + 5, -1));
        int offset = 1;

        auto f = [&](int i, int prev, auto && f) -> int {
            if (i == n) return 0;
            if (dp[i][prev + offset] != -1) return dp[i][prev + offset];

            int ans = 0;

            if (prev == -1) {
                int skip = f(i + 1, prev, f);
                int take = 1 + f(i + 1, i, f);
                ans = max(skip, take);
            } 
            else {
                if (a[i] > a[prev]) {
                    int skip = f(i + 1, prev, f);
                    int take = 1 + f(i + 1, i, f);
                    ans = max(skip, take);
                } else {
                    int skip = f(i + 1, prev, f);
                    ans = skip;
                }
            }

            return dp[i][prev + offset] = ans;
        };

        return f(0, -1, f);
    }
};

/*
=======================================================================================
APPROACH 2: Binary Search / Patience Sorting (The Optimal Approach)
Time Complexity: O(N log N) | Space Complexity: O(N)
=======================================================================================
The Core Philosophy: "Greedy for Runway"
- Imagine finding two valid increasing subsequences of length 3: [1, 5, 9] and [1, 2, 4].
- Which one is better? [1, 2, 4] is immensely better because it ends in 4. 
- Ending in 4 leaves a massive "runway" to append future numbers (anything > 4). 
  Ending in 9 leaves almost no room to grow.
- GOLDEN RULE: For any given length L, we ONLY care about the sequence that ends 
  in the smallest possible number.

Building the "Tail" Array:
- `tail[i]` stores the smallest ending number for an increasing subsequence of length i + 1.
- Trace Example on array [3, 10, 2, 1, 20]:
    1. Process 3: tail = [3]
    2. Process 10: 10 > 3. Append it. tail = [3, 10]
    3. Process 2: 2 <= 10. But a length-1 sequence ending in 2 is better than one 
       ending in 3! Overwrite 3. tail = [2, 10]
    4. Process 1: 1 <= 10. Length-1 ending in 1 is even better. Overwrite 2. 
       tail = [1, 10]
    5. Process 20: 20 > 10. Append it. tail = [1, 10, 20]
- The final size of `tail` is 3. That is our Longest Increasing Subsequence length!

Why Binary Search?
- Because we only append strictly greater elements, `tail` is ALWAYS strictly sorted.
- When we find a number that cannot be appended, we don't need a linear scan to find 
  who to overwrite. We use binary search (`lower_bound`) to instantly find the first 
  number >= current element in O(log N) time.

The Mind-Bending Catch (The "Ghost Sequence"):
- Look at tail = [1, 10]. In the original array, 1 comes AFTER 10. 
- The `tail` array DOES NOT store the literal final subsequence! It acts as an 
  independent tracker for the best possible endings at different lengths. 
- Overwriting 3 with 1 just says: "From this point forward, if I need a length-1 
  sequence to build upon, I'll use 1." The 10 safely stayed in its slot, representing 
  a valid length-2 sequence established earlier.
=======================================================================================
*/
class Solution2 {
public:
    int lengthOfLIS(vector<int>& a) {
        int n = a.size();
        
        // This array will store the smallest tail elements of increasing subsequences
        vii tail;

        for (int i = 0; i < n; i++) {
            
            // CASE 1: The current element is strictly greater than the last element of tail.
            // It safely extends our longest subsequence.
            if (tail.empty() || a[i] > tail.back()) {
                tail.pb(a[i]);
            } 
            // CASE 2: We can't extend, but we can optimize a previous tail to be smaller.
            else {
                // lower_bound uses Binary Search (O(log N)) to find the first element >= a[i]
                int idx = lower_bound(all(tail), a[i]) - tail.begin();
                
                // Overwrite it with the smaller value to increase our "runway"
                tail[idx] = a[i];
            }
        }

        // The size of the tail array strictly represents the maximum length found
        return tail.size();
    }
};