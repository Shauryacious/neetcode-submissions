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
#define INF 1e9 
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
#define all(x) (x).begin(), (x).end()

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
PATTERN: Greedy Queue Simulation
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
EXPLANATION OF LOGIC:
1. Load all 'R' indices into queue `qR` and all 'D' indices into `qD`.
2. While both factions have surviving members, pit the fronts against each other.
3. The senator with the smaller index acts first. They eliminate the other.
4. The survivor moves to the NEXT round by having `n` added to their index and is 
   pushed to the back of their respective queue.
5. The loop terminates when one faction is wiped out. Return the winner.
=======================================================================================
*/

class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = sz(senate);
        queue<int> qR;
        queue<int> qD;
        
        // Step 1: Populate the initial indices into the queues
        for (int i = 0; i < n; i++) {
            if (senate[i] == 'R') {
                qR.push(i);
            } else {
                qD.push(i);
            }
        }
        
        // Step 2: Simulate the rounds until one party is annihilated
        while (!qR.empty() && !qD.empty()) {
            int r_idx = qR.front();
            int d_idx = qD.front();
            
            qR.pop();
            qD.pop();
            
            // The senator with the smaller index acts first and survives
            if (r_idx < d_idx) {
                // Radiant wins this duel. 
                // Add 'n' to schedule them for the next round.
                qR.push(r_idx + n);
            } else {
                // Dire wins this duel.
                // Add 'n' to schedule them for the next round.
                qD.push(d_idx + n);
            }
        }
        
        // Step 3: The non-empty queue is the ultimate victor
        return qR.empty() ? "Dire" : "Radiant";
    }
};