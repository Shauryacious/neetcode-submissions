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
#include<functional>
#include<iterator>
#include<cstring>

using namespace std;


#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define pb push_back
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


class Solution {
private:
    vii PSE(vii& a) {
        int n = a.size();
        vii ans(n);
        stack<int> st;

        //PPAP  -> Pop Ans Push
        for(int i=0; i<n; i++) {
            // PoP karo jab tab tumse bada ya barabar element top pe h 
            while(!st.empty() && a[st.top()] >= a[i]) {
                st.pop();
            }

            //Ans
            if(st.empty()) {
                ans[i] = -1;
            } else {
                ans[i] = st.top();
            }

            // Push 
            st.push(i);
        }
        return ans;
    }

    vii NSE(vii& a) {
        int n = a.size();
        vii ans(n);
        stack<int> st;

        //PPAP  -> Pop Ans Push
        for(int i=n-1; i>=0; i--) {
            // PoP karo jab tab tumse bada ya barabar element top pe h 
            while(!st.empty() && a[st.top()] >= a[i]) {
                st.pop();
            }

            //Ans
            if(st.empty()) {
                ans[i] = n;
            } else {
                ans[i] = st.top();
            }

            // Push 
            st.push(i);
        }
        return ans;
    }


public:
    int largestRectangleArea(vector<int>& a) {
        int n = a.size();
        vii pse = PSE(a);
        vii nse = NSE(a);

        int ans = 0;
        for(int i=0; i<n; i++) {
            int width = nse[i] - pse[i] - 1;
            int height = a[i];
            int area = height * width;
            ans = max(ans, area);
        }

        return ans;
    }
};