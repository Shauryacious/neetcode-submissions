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
PATTERN: Two Multisets (Simulating Two Heaps)
Time Complexity: O(log N) per add | O(1) per median query
Space Complexity: O(N) to store the stream
=======================================================================================
Explanation:
- `left_max` uses `greater<int>` to act as a Max-Heap. Max is at `*begin()`.
- `right_min` uses default sorting to act as a Min-Heap. Min is at `*begin()`.
- We use `.insert(val)` to push.
- We strictly use `.erase(ms.begin())` to pop. This guarantees we only remove ONE 
  node, avoiding the catastrophic bug of deleting all duplicate values.
=======================================================================================
*/

class MedianFinder {
private:
    // Acts as Max-Heap (Descending order)
    multiset<int, greater<int>> left_max;
    
    // Acts as Min-Heap (Ascending order)
    multiset<int> right_min;

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // 1. Trust Fall into the Left side
        left_max.insert(num);
        
        // 2. Filter: Move the top of left_max into right_min
        right_min.insert(*left_max.begin());
        left_max.erase(left_max.begin()); // MUST erase by iterator!
        
        // 3. Balance: Left must ALWAYS be >= Right in size
        if (right_min.size() > left_max.size()) {
            left_max.insert(*right_min.begin());
            right_min.erase(right_min.begin()); // MUST erase by iterator!
        }
    }
    
    double findMedian() {
        // If total count is odd, left_max holds the exact median
        if (left_max.size() > right_min.size()) {
            return *left_max.begin();
        } 
        // If total count is even, average the two middle boundaries
        else {
            return (*left_max.begin() + *right_min.begin()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */