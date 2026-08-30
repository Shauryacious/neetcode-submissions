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
PATTERN: Two Pointers (Interval Intersection)
Time Complexity: O(M + N) | Space Complexity: O(1) Auxiliary
Where M and N are the sizes of the two interval lists.
=======================================================================================
EXPLANATION OF LOGIC:
- We calculate the potential bounds of an intersection using max(starts) and min(ends).
- If `start_max <= end_min`, a valid overlap is proven and we push it to the answer.
- We then look at the end times: `end_i` and `end_j`. 
- Whichever interval ends first is fundamentally exhausted and can never intersect 
  with any upcoming intervals. We advance its respective pointer.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vvii ans;
        int i = 0;
        int j = 0;
        
        while (i < firstList.size() && j < secondList.size()) {
            
            // Strictly unpack variables for absolute clarity
            int start_i = firstList[i][0];
            int end_i   = firstList[i][1];
            
            int start_j = secondList[j][0];
            int end_j   = secondList[j][1];
            
            // Calculate the potential overlap boundaries
            int start_max = max(start_i, start_j);
            int end_min   = min(end_i, end_j);
            
            // If the boundaries are valid, an intersection exists
            if (start_max <= end_min) {
                ans.pb({start_max, end_min});
            }
            
            // Discard the interval that finishes earlier
            if (end_i < end_j) {
                i++;
            } else {
                j++;
            }
        }
        
        return ans;
    }
};