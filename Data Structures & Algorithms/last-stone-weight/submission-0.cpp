// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<set>

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
APPROACH: Multiset (Balanced BST) Simulation
Time Complexity: O(N log N) | Space Complexity: O(N)
=======================================================================================
Intuition & Visualization:
- We initialize a `multiset` with `greater<int>`. This instantly sorts our stones 
  descending, allowing duplicates.
- The heaviest stone is always sitting precisely at `ms.begin()`.
- We grab the heaviest stone (`y`) and carefully erase ONLY that specific iterator.
- We immediately grab the new heaviest stone (`x`) and erase its iterator.
- If `y > x`, we insert the surviving fragment back into the tree. The tree will 
  automatically route it to its perfect sorted position in O(log N) time!
=======================================================================================
*/
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        // Initialize the multiset in descending order
        multiset<int, greater<int>> ms(all(stones));
        
        while (ms.size() > 1) {
            // Grab the heaviest stone
            int y = *ms.begin();
            // Erase ONLY the iterator, not the value!
            ms.erase(ms.begin());
            
            // Grab the second heaviest stone
            int x = *ms.begin();
            ms.erase(ms.begin());
            
            // If a fragment survives, insert it back into the BST
            if (y > x) {
                ms.insert(y - x);
            }
        }
        
        if (ms.empty()) {
            return 0;
        }
        
        return *ms.begin();
    }
};