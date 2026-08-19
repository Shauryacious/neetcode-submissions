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
PATTERN: Top 'K' Smallest Elements (Multiset)
Time Complexity: O(N log K) strictly one pass | Space: O(K) auxiliary size
=======================================================================================
Explanation:
- We use a `multiset` of pairs: `{squared_distance, point_vector}`.
- C++ automatically sorts pairs by their first element (the distance).
- We unconditionally insert the new point into the set.
- If the size exceeds `k`, we kick out the FARTHEST point. In an ascending multiset, 
  the largest element is at the end, so we erase `prev(mst.end())`.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        
        // multiset to store {squared_distance, point_coordinates}
        multiset<pair<int, vector<int>>> mst;
        
        for (auto& p : points) {
            
            // Calculate squared Euclidean distance to (0, 0)
            int dist = (p[0] * p[0]) + (p[1] * p[1]);
            
            // 1. Unconditionally insert the new point
            mst.insert({dist, p});
            
            // 2. Trim the excess by kicking out the point with the LARGEST distance
            if (mst.size() > k) {
                // prev(mst.end()) gets the iterator to the last (largest) element
                mst.erase(prev(mst.end()));
            }
        }
        
        vvii ans;
        
        // The multiset now contains exactly the K closest points
        for (auto& it : mst) {
            ans.pb(it.second);
        }
        
        return ans;
    }
};