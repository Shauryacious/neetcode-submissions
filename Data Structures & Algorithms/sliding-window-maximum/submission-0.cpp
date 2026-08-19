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
#include<queue>
#include<deque>

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
APPROACH 1: The Brute Force (Time Limit Exceeded)
=======================================================================================
Explanation:
This is the most naive way to solve the problem. We strictly define the sliding window 
boundaries `i` and `j`. For every valid window of size `k`, we run a nested loop 
from `i` to `j` to manually scan for the maximum value.

Time Complexity: $O(N \times K)$
For every window of size `K`, we scan `K` elements. If $N = 10^5$ and $K = 50,000$, 
this executes $5 \times 10^9$ operations, which guarantees a TLE.

Space Complexity: $O(1)$ auxiliary space (excluding the answer array).
=======================================================================================
*/
class Solution1 {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        int n = a.size();
        vii ans;
        
        int i = 0, j = 0;
        
        while (j < n) {
            if (j - i + 1 == k) {
                int current_max = -INF;
                // Manually scan the window for the maximum
                for (int x = i; x <= j; x++) {
                    current_max = max(current_max, a[x]);
                }
                ans.pb(current_max);
                
                i++; // Shrink window
            }
            j++; // Advance window
        }
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Balanced Binary Search Tree (`std::multiset`)
=======================================================================================
Explanation:
To avoid manually scanning the window, we can maintain the elements inside a `multiset`. 
A `multiset` is implemented as a Red-Black Tree, which automatically keeps all elements 
sorted. The maximum element is always at the very end of the set, accessible via `.rbegin()`.
Crucially, when shrinking the window, we must use `ms.erase(ms.find(a[i]))` to delete 
only ONE instance of the outgoing element, rather than all copies of it.

Time Complexity: $O(N \log K)$
Inserting and erasing elements from a Red-Black Tree takes $O(\log K)$ time.

Space Complexity: $O(K)$
The `multiset` holds exactly `K` elements at any time.
=======================================================================================
*/
class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        int n = a.size();
        vii ans;
        multiset<int> ms;
        
        int i = 0, j = 0;
        
        while (j < n) {
            // 1. Insert
            ms.insert(a[j]);
            
            // 2. Evaluate
            if (j - i + 1 == k) {
                ans.pb(*ms.rbegin());
                
                // 3. Shrink: Find the iterator to one instance of a[i] and erase it
                ms.erase(ms.find(a[i]));
                i++;
            }
            
            // 4. Advance
            j++;
        }
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 3: Max-Heap (Priority Queue) with Lazy Deletion
=======================================================================================
Explanation:
A priority queue (Max-Heap) gives us the maximum element in $O(1)$ time. However, 
heaps do not support removing arbitrary elements (like `a[i]`) efficiently. 
To bypass this, we store pairs of `{value, index}` in the heap. We simply push every 
element into the heap. When evaluating the window max, we check the index of the top 
element. If the index is less than `i`, it has fallen out of our window! We pop it 
and check the next top element (Lazy Deletion).

Time Complexity: $O(N \log N)$ worst-case.
If the array is strictly decreasing, the expired elements never float to the top 
to get lazily deleted until the very end. The heap size grows to $N$. Pushing into 
a heap of size $N$ takes $O(\log N)$.

Space Complexity: $O(N)$
In the worst-case, the heap stores all $N$ elements.
=======================================================================================
*/
class Solution3 {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        int n = a.size();
        vii ans;
        priority_queue<pair<int, int>> pq; 
        
        int i = 0, j = 0;
        
        while (j < n) {
            // 1. Insert pair {value, index}
            pq.push({a[j], j});
            
            // 2. Evaluate
            if (j - i + 1 == k) {
                
                // Lazy Deletion: keep popping until the top element is inside our window
                while (pq.top().second < i) {
                    pq.pop();
                }
                
                ans.pb(pq.top().first);
                
                // 3. Shrink
                i++;
            }
            
            // 4. Advance
            j++;
        }
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 4: Monotonic Deque (The Standard Optimal)
=======================================================================================
Explanation:
Instead of a heap, we use a doubly-ended queue (`deque`) to store indices. We strictly 
maintain the deque in decreasing order of their corresponding values. 
When a new element `a[j]` arrives, it makes all smaller elements currently in the deque 
completely useless (because `a[j]` is larger AND will stay in the window longer). 
We `pop_back` all these useless elements before inserting `j`. The front of the deque 
always holds the index of the current maximum.

Time Complexity: $O(N)$
Every element is pushed into the deque exactly once and popped at most once. 

Space Complexity: $O(K)$
The deque holds at most `K` indices at any given time.
=======================================================================================
*/
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        int n = a.size();
        vii ans;
        deque<int> dq; 
        
        int i = 0, j = 0;
        
        while (j < n) {
            // 1. Insert: Maintain Monotonic Decreasing property
            while (!dq.empty() && a[dq.back()] <= a[j]) {
                dq.pop_back();
            }
            dq.push_back(j);
            
            // 2. Evaluate
            if (j - i + 1 == k) {
                ans.pb(a[dq.front()]);
                
                // 3. Shrink: If the max element's index matches our left boundary, it expires
                if (dq.front() == i) {
                    dq.pop_front();
                }
                i++;
            }
            
            // 4. Advance
            j++;
        }
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 5: Dynamic Programming / Block Decomposition (Legendary Tier)
=======================================================================================
Explanation:
This approach completely avoids advanced data structures. We divide the array into blocks 
of exactly size `k`. 
We build a `left_max` array: the running maximum from the start of the block to the right.
We build a `right_max` array: the running maximum from the end of the block to the left.
Any sliding window `[i, j]` either perfectly fits in one block, or spans across exactly 
two blocks. The maximum of that window is simply the max of the right-suffix of the 
first block (`right_max[i]`) and the left-prefix of the second block (`left_max[j]`).

Time Complexity: $O(N)$
We do a few linear passes over the array to build the prefix/suffix max arrays, and 
one linear pass to construct the answer.

Space Complexity: $O(N)$
We need to allocate memory for the `left_max` and `right_max` arrays.
=======================================================================================
*/
class Solution5 {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        int n = a.size();
        if (n == 0 || k == 0) return {};
        if (k == 1) return a;
        
        vii left_max(n), right_max(n);
        left_max[0] = a[0];
        right_max[n - 1] = a[n - 1];
        
        // Build the prefix and suffix maximums block by block
        for (int i = 1; i < n; i++) {
            
            // Left to Right pass
            if (i % k == 0) {
                left_max[i] = a[i];  // Start of a new block
            } else {
                left_max[i] = max(left_max[i - 1], a[i]);
            }
            
            // Right to Left pass
            int j = n - i - 1;
            if ((j + 1) % k == 0) {
                right_max[j] = a[j]; // End of a block
            } else {
                right_max[j] = max(right_max[j + 1], a[j]);
            }
        }
        
        vii ans;
        
        // Evaluate the window maxes using the precomputed arrays
        for (int i = 0; i <= n - k; i++) {
            int j = i + k - 1;
            ans.pb(max(right_max[i], left_max[j]));
        }
        
        return ans;
    }
};