// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>

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
SOLUTION 1: Two Queues (Transfer Approach)
Time Complexity: O(N) for push(), O(1) for pop(), top(), empty() 
Space Complexity: O(N) auxiliary space for two queues
=======================================================================================
Intuition & Visualization:
- We use two queues: `q1` (main storage) and `q2` (temporary transfer queue).
- `push(x)`: When a new element arrives, we push it to the empty `q2` first.
- Then, we transfer all existing elements from `q1` into `q2` right behind the new element.
- Finally, we swap the names/contents of `q1` and `q2`. Now `q1` has the newest element 
  at the absolute front, simulating the top of a stack.
- `pop()` and `top()` simply interact with the front of `q1`.
=======================================================================================
*/
class MyStack1 {
private:
    queue<int> q1;
    queue<int> q2;

public:
    MyStack1() {}
    
    void push(int x) {
        // Step 1: Push new element to the empty auxiliary queue
        q2.push(x);
        
        // Step 2: Transfer all older elements from q1 to q2 behind the new element
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // Step 3: Swap q1 and q2 so q1 remains our main operational queue
        swap(q1, q2);
    }
    
    int pop() {
        int top_element = q1.front();
        q1.pop();
        return top_element;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/*
=======================================================================================
SOLUTION 2: The Single Queue "VIP Rotation" (Optimal)
Time Complexity: O(N) for push(), O(1) for pop(), top(), empty() 
Space Complexity: O(N) total space, but uses 1 less queue (Better memory footprint)
=======================================================================================
Intuition & Visualization:
- We optimize the previous approach by eliminating the need for `q2` entirely.
- `push(x)`: When `x` arrives, we push it to the back of the queue. To make it behave 
  like a Stack, `x` needs to be at the front! We achieve this by rotating all the older 
  elements behind `x`. 
- We record the size `s` BEFORE adding `x`, add `x`, and then pop the front element 
  and push it to the back exactly `s` times.
- `pop()`: Since our `push` operation guarantees the newest element is always sitting 
  perfectly at the front of the queue, `pop` is just a standard queue pop!
=======================================================================================
*/
class MyStack {
private:
    queue<int> q;

public:
    MyStack() {}
    
    void push(int x) {
        // Record the number of older elements currently in the queue
        int s = q.size();
        
        // Push the new element to the back
        q.push(x);
        
        // Rotate all the older elements to the back, one by one.
        // This shifts the newly added element right to the front!
        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        // The newest element is safely resting at the front
        int top_element = q.front();
        q.pop();
        return top_element;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/**
 * Object Instantiation Example:
 * Solution2* obj = new Solution2();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */