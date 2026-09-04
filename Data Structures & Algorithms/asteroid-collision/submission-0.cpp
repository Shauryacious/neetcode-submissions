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
PATTERN: Stack Simulation (Branch-Based Collision Logic)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
EXPLANATION OF LOGIC:
1. Positive asteroids move right and are safely pushed onto the stack.
2. Negative asteroids trigger collisions only when the stack top is positive.
3. The while loop handles the collision mechanics:
   - Smaller positive asteroids on the stack are popped off.
   - Equal-sized asteroids cause mutual destruction (`destroied = true`).
   - Larger positive asteroids destroy the incoming negative asteroid.
4. Finally, elements are extracted from the stack and reversed to restore order.
=======================================================================================
*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& a) {
        int n = a.size();
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) { 
                // Right-moving asteroid: no immediate collision risk with stack elements
                st.push(a[i]);
            } 
            else { 
                // Left-moving asteroid
                if (st.empty()) {
                    st.push(a[i]);
                } 
                else if (st.top() < 0) { 
                    // Stack top is also moving left; parallel motion means no collision
                    st.push(a[i]);
                } 
                else { 
                    // Stack top is positive (moving right): collision imminent!
                    bool destroied = false;
                    
                    while (!st.empty() && st.top() > 0) {
                        int x = st.top();
                        
                        if (x < abs(a[i])) {
                            // Stack top is smaller; it explodes, but incoming keeps moving
                            st.pop();   
                            continue;               
                        } 
                        else if (x == abs(a[i])) { 
                            // Both explode
                            destroied = true;
                            st.pop();
                            break; 
                        } 
                        else { 
                            // Stack top is larger; incoming asteroid is destroyed
                            destroied = true;
                            break; 
                        }
                    }
                    
                    if (destroied == false) {
                        st.push(a[i]);
                    }
                }
            }
        }

        // Extract result from stack
        vector<int> ans;
        while (!st.empty()) {     
            ans.push_back(st.top());
            st.pop();
        }

        // Restore correct left-to-right order
        reverse(ans.begin(), ans.end());
        return ans;
    }
};