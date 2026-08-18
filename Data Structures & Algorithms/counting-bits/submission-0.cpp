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
#include<functional>
#include<iterator>
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

class Solution {
    int dp[100005]; // Constraint says n is up to 10^5
public:
    vector<int> countBits(int n) {
        
        // State: 
        // dp[i] = the number of 1's in the binary representation of i.
        
        // Base Case: 
        // If i == 0, the binary representation is 0, which has zero 1's.
        
        memset(dp, -1, sizeof(dp));

        auto f = [&](int i, auto && f) -> int {
            // Base case
            if (i == 0) return 0;

            if (dp[i] != -1) return dp[i];

            int ans = 0;

            // Logic:
            // Right-shifting by 1 (i / 2) removes the least significant bit.
            // We recursively count the bits of (i / 2).
            // Then we add 1 ONLY if the least significant bit was a 1 (i.e., if i is odd).
            int shifted_bits = f(i / 2, f);
            int last_bit = i % 2; 

            ans = shifted_bits + last_bit;

            return dp[i] = ans;
        };

        vii result;
        // Build the answer array from 0 to n
        for(int i = 0; i <= n; i++) {
            result.pb(f(i, f));
        }

        return result;
    }
};