// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
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

/*
=======================================================================================
APPROACH: The "Historical Snapshot" (Vector of Pairs)
Time Complexity: O(1) for all operations | Space Complexity: O(N) 
=======================================================================================
Intuition & Visualization:
- We use a dynamic array (`vector`) to simulate our stack. 
- Each entry in the stack is a pair: {val, current_min}
- `push(val)`: 
    - If the stack is empty, the new element is inherently the minimum. We push `{val, val}`.
    - If not empty, the new minimum is simply the minimum between the new `val` and 
      the `current_min` stored in the backpack of the top element.
- `pop()`: We just remove the last pair. The previous minimum is instantly restored!
- `top()`: Return the `.first` value of the top pair.
- `getMin()`: Return the `.second` value (the backpack) of the top pair.
=======================================================================================
*/
class MinStack {
private:
    // Pair structure: {actual_value, min_value_so_far}
    vpii st; 

public:
    MinStack() {
        // Constructor, no explicit initialization needed for vector
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push_back({val, val});
        } 
        else {
            // The new minimum is either the new value, or the old minimum.
            int current_min = min(val, st.back().second);
            st.push_back({val, current_min});
        }
    }
    
    void pop() {
        // The problem guarantees pop is always called on non-empty stacks
        st.pop_back();
    }
    
    int top() {
        return st.back().first;
    }
    
    int getMin() {
        return st.back().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */