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
SOLUTION 1: Pure Stack Simulation
Time Complexity: O(N) | Space Complexity: O(N) auxiliary stack space

EXPLANATION:
This strictly adheres to the Last-In-First-Out (LIFO) principle using `std::stack`.
While logically sound, the '+' operation is mechanically expensive because a pure 
stack does not allow random access. We must pop the top two elements, calculate 
their sum, and then push all three elements back onto the stack in the correct order.
=======================================================================================
*/

class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        
        // Zero-copy loop using auto& 
        for (auto& op : operations) {
            if (op == "+") {
                // Manually extract top two elements
                int top1 = st.top();
                st.pop();

                int top2 = st.top();
                st.pop();

                // Push them back in original order, followed by the sum
                st.push(top2);
                st.push(top1);
                st.push(top1 + top2);
            } 
            else if (op == "D") {
                st.push(st.top() * 2);
            } 
            else if (op == "C") {
                st.pop();
            } 
            else {
                st.push(stoi(op));
            }
        }
        
        int total_sum = 0;
        
        // Destructive accumulation (destroys the stack to read it)
        while(st.size() > 0) {
            total_sum += st.top();
            st.pop();
        }
        
        return total_sum;
    }
};

/*
=======================================================================================
SOLUTION 2: Optimized Vector as Stack (Recommended for CP)
Time Complexity: O(N) | Space Complexity: O(N) auxiliary vector space

EXPLANATION & OPTIMIZATIONS:
By using `std::vector`, we maintain LIFO capabilities (using `pb` and `ppb`) but gain 
O(1) random access. 
- Optimization 1: For the '+' operation, we simply read `st.back()` and `st[sz(st) - 2]` 
  directly. No popping and re-pushing required.
- Optimization 2: Accumulating the final sum is done via a fast range-based for-loop 
  instead of destructively popping every element with a while loop.
=======================================================================================
*/

class Solution2 {
public:
    int calPoints(vector<string>& operations) {
        vector<int> st;
        
        // Zero-copy loop using auto&
        for (auto& op : operations) {
            if (op == "+") {
                // O(1) random access eliminates the need to pop and repush
                int top1 = st.back();
                int top2 = st[sz(st) - 2];
                st.pb(top1 + top2);
            } 
            else if (op == "D") {
                st.pb(st.back() * 2);
            } 
            else if (op == "C") {
                st.ppb();
            } 
            else {
                st.pb(stoi(op));
            }
        }
        
        int total_sum = 0;
        
        // Non-destructive, cache-friendly iteration
        for (auto& score : st) {
            total_sum += score;
        }
        
        return total_sum;
    }
};