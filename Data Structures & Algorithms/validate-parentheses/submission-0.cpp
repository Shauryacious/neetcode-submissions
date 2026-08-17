// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
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
APPROACH 1: The Standard Stack
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
Intuition:
- We use the C++ STL `stack` to keep track of the open brackets.
- When we encounter a closing bracket, we check if the `stack.top()` is its 
  corresponding open bracket.
- Edge case: If we encounter a closing bracket but the stack is `empty()`, it means 
  there is no open bracket to match it with (e.g., string starts with `]`).
=======================================================================================
*/
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s) {
            // If it's an opening bracket, push it to the stack
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } 
            // If it's a closing bracket
            else {
                // If stack is empty, we can't match this closing bracket
                if (st.empty()) return false;

                char top = st.top();
                
                // If it's a perfect match, pop it!
                if ((c == ')' && top == '(') || (c == '}' && top == '{') || (c == ']' && top == '[')) {
                    st.pop();
                } 
                // If it doesn't match, the string is invalid
                else {
                    return false;
                }
            }
        }

        // If the stack is empty at the end, every open bracket was matched.
        return st.empty();
    }
};

/*
=======================================================================================
APPROACH 2: In-Place Stack (The O(1) Auxiliary Space Flex)
Time Complexity: O(N) | Space Complexity: O(1) auxiliary
=======================================================================================
Intuition:
- Do we really need to allocate a separate `stack<char>` data structure?
- C++ strings are completely mutable (we can overwrite characters).
- We can use the original string `s` as our stack! We just maintain a `top` pointer 
  that tracks the index of our virtual stack.
- As we iterate with `i`, if it's an open bracket, we move our `top` pointer forward 
  and write the open bracket there. If it's a closing bracket, we check `s[top]`.
- This reduces the extra memory allocation to absolute zero.
=======================================================================================
*/
class Solution2 {
public:
    bool isValid(string s) {
        // 'top' acts as the pointer for our in-place stack.
        // -1 means our virtual stack is empty.
        int top = -1;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];

            if (c == '(' || c == '{' || c == '[') {
                top++;
                s[top] = c; // Push to our virtual stack
            } 
            else {
                // If trying to pop from an empty stack
                if (top == -1) return false;

                // Check the top of our virtual stack
                if ((c == ')' && s[top] == '(') || (c == '}' && s[top] == '{') || (c == ']' && s[top] == '[')) {
                    top--; // Pop from our virtual stack
                } 
                else {
                    return false;
                }
            }
        }

        // If 'top' is back to -1, everything matched perfectly.
        return top == -1;
    }
};