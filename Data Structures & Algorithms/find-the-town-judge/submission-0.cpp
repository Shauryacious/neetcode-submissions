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
APPROACH 1: Explicit In-Degree and Out-Degree Arrays (Pure Graph Theory)
Time Complexity: O(V + E) | Space Complexity: O(V)
=======================================================================================
Explanation:
- We treat the people as nodes and trust relationships as directed edges.
- We maintain two separate arrays: `in_degree` (how many people trust this person) 
  and `out_degree` (how many people this person trusts).
- For every edge [a, b], 'a' gets an out-degree, and 'b' gets an in-degree.
- Finally, we scan the arrays. The judge is the singular person who satisfies both:
  1. in_degree == n - 1
  2. out_degree == 0
=======================================================================================
*/

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        
        // 1-indexed arrays for explicit graph properties
        vii in_degree(n + 1, 0);
        vii out_degree(n + 1, 0);
        
        // Populate the degrees
        for (auto& edge : trust) {
            int u = edge[0]; // Truster
            int v = edge[1]; // Trustee
            
            out_degree[u]++;
            in_degree[v]++;
        }
        
        // Verify the dual properties of the Town Judge
        for (int i = 1; i <= n; i++) {
            if (in_degree[i] == n - 1 && out_degree[i] == 0) {
                return i;
            }
        }
        
        return -1; 
    }
};


/*
=======================================================================================
APPROACH 2: Net Trust Score Array (Memory Compression)
Time Complexity: O(V + E) | Space Complexity: O(V)
=======================================================================================
Explanation:
- We merge the two arrays into a single `trust_score` array.
- Out-degree acts as a penalty (-1), and in-degree acts as a reward (+1).
- Because a valid judge must have an in-degree of `n - 1` and an out-degree of `0`, 
  their final net score will be exactly `n - 1`.
- If a person trusts even one other person, their maximum possible score drops 
  to `(n - 1) - 1 = n - 2`, instantly disqualifying them.
=======================================================================================
*/

class Solution2 {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        
        // Single array to track the mathematical net score
        vii trust_score(n + 1, 0);
        
        // Process the directed edges as penalties and rewards
        for (auto& edge : trust) {
            int u = edge[0]; 
            int v = edge[1]; 
            
            trust_score[u]--; // Penalty for trusting someone
            trust_score[v]++; // Reward for being trusted
        }
        
        // The judge is the only one who collects all rewards and zero penalties
        for (int i = 1; i <= n; i++) {
            if (trust_score[i] == n - 1) {
                return i;
            }
        }
        
        return -1; 
    }
};