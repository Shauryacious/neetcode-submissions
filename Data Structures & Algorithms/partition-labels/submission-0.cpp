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
PATTERN: Greedy / Expanding Window
Time Complexity: O(N) two passes | Space Complexity: O(1) auxiliary (size 26 array)
=======================================================================================
Explanation:
- We first record the last index of every character using a frequency array of size 26.
- We iterate through the string maintaining a `start` and `end` boundary.
- For each character `s[i]`, we aggressively push `end` to its furthest last occurrence.
- If `i == end`, it guarantees no character inside the current window exists beyond `i`.
- We record the chunk size (`end - start + 1`) and reset `start` for the next chunk.
=======================================================================================
*/

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = sz(s);
        vii ans;
        
        // Array to store the last occurrence index of each character
        vii last_idx(26, 0);
        
        // Pass 1: Record the last occurrence of each character
        for (int i = 0; i < n; i++) {
            last_idx[s[i] - 'a'] = i;
        }
        
        int start = 0;
        int end = 0;
        
        // Pass 2: Greedily determine the partitions
        for (int i = 0; i < n; i++) {
            
            // Expand the window's required end to the farthest last occurrence of current character
            end = max(end, last_idx[s[i] - 'a']);
            
            // If our current index catches up to the required end boundary, the partition is complete!
            if (i == end) {
                ans.pb(end - start + 1);
                
                // Shift the start boundary for the next partition
                start = i + 1;
            }
        }
        
        return ans;
    }
};