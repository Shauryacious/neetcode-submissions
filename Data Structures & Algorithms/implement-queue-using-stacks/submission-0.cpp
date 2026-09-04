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
#include<stack>

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
SOLUTION 1: Brute Force (Push-Heavy)
Time Complexity: O(N) for push(), O(1) for pop(), peek(), empty()
Space Complexity: O(N) auxiliary space for two stacks
=======================================================================================
Intuition & Visualization:
- We use two stacks: `s1` (main) and `s2` (transfer).
- `push(x)`: We want the oldest elements to always stay at the top of `s1`. 
  To put the newest element at the absolute bottom, we move everything from `s1` to `s2`, 
  push the new element into the now-empty `s1`, and then dump `s2` back into `s1`.
- Because `s1` is strictly maintained in FIFO order, `pop` and `peek` are instant O(1).
=======================================================================================
*/
class MyQueue1 {
private:
    stack<int> s1;
    stack<int> s2;

public:
    MyQueue1() {}
    
    void push(int x) {
        // Step 1: Move all existing elements to the transfer stack
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        
        // Step 2: Place the newest element at the very bottom of the main stack
        s1.push(x);
        
        // Step 3: Move all older elements back on top to preserve FIFO order
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    int pop() {
        int front_element = s1.top();
        s1.pop();
        return front_element;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal "Amortized O(1)" (Lazy-Transfer)
Time Complexity: Amortized O(1) for all operations (Worst-case O(N) for a single pop)
Space Complexity: O(N) auxiliary space
=======================================================================================
Intuition & Visualization:
- We use an `input` stack and an `output` stack.
- `push(x)`: Always instant! Just throw it into `input` in O(1) time.
- `pop()` / `peek()`: We only need elements in reverse order when someone asks for them. 
  If `output` is empty, we dump everything from `input` into `output`. This reverses 
  their order perfectly! We only do this heavy O(N) dump when `output` is completely 
  empty, meaning over N operations, the cost averages out to O(1) per operation.
=======================================================================================
*/
class MyQueue {
private:
    stack<int> input;
    stack<int> output;

public:
    MyQueue() {}
    
    void push(int x) {
        // Just throw the new element into the input stack (O(1))
        input.push(x);
    }
    
    int pop() {
        // Ensure the output stack is prepped with the oldest elements
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        
        // Pop from the prepped output stack
        int front_element = output.top();
        output.pop();
        return front_element;
    }
    
    int peek() {
        // Ensure the output stack is prepped
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        
        // Peek at the prepped output stack
        return output.top();
    }
    
    bool empty() {
        // The queue is only empty if BOTH stacks are empty
        return input.empty() && output.empty();
    }
};

/**
 * Object Instantiation Example:
 * Solution2* obj = new Solution2();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */