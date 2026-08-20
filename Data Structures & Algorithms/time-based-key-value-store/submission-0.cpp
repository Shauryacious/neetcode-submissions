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
PATTERN: HashMap + Custom Binary Search
Time Complexity: 
  - set(): O(1) amortized
  - get(): O(log N) where N is the number of timestamps for the requested key
Space Complexity: O(Total number of set operations) for the unordered_map
=======================================================================================
Explanation:
- We map each `string` key to a `vector` of `pair<timestamp, value>`.
- Because `set` is called with strictly increasing timestamps, `pb` keeps it sorted.
- In `get`, we perform a standard Binary Search over the key's vector.
- If `v[mid].ff <= timestamp`, we have a valid answer! We save it, but we push 
  `low = mid + 1` to greedily hunt for a larger timestamp that might still be valid.
=======================================================================================
*/

class TimeMap {
private:
    // Hash map tying a key to a historical timeline of (timestamp, value) pairs
    unordered_map<string, vector<pair<int, string>>> m;
    
public:
    TimeMap() {
        // Automatically initialized, but good practice to clear if object is reused
        m.clear();
    }
    
    void set(string key, string value, int timestamp) {
        // Appends in O(1) time. Guaranteed to remain sorted!
        m[key].pb(mp(timestamp, value));
    }
    
    string get(string key, int timestamp) {
        // If the key doesn't exist at all, return empty string
        if (m.find(key) == m.end()) {
            return "";
        }
        
        // Reference the timeline array for speed
        auto& v = m[key];
        
        int low = 0;
        int high = sz(v) - 1;
        string ans = "";
        
        // Binary search for the largest timestamp <= target
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // v[mid].ff is the timestamp
            if (v[mid].ff <= timestamp) {
                ans = v[mid].ss;    // This value is valid! Record it.
                low = mid + 1;      // But try to find a more recent valid timestamp
            } else {
                high = mid - 1;     // The timestamp is in the future, look left
            }
        }
        
        return ans;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */