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
APPROACH: Greedy / Running Minimum
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Problem: Best Time to Buy and Sell Stock

Intuition:
- We want to maximize `profit = sell - buy`.
- If we consider the current day `i` as the selling day, we want the buying day 
  to be the absolute lowest price we have seen so far to the left of `i`.
- By keeping a running minimum (`min_buy`), we can calculate the max possible 
  profit for every single day in just one pass!
=======================================================================================
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        int min_buy = prices[0];
        int max_profit = 0;
        
        for (int i = 1; i < n; i++) {
            // Update the maximum profit if we sell today
            max_profit = max(max_profit, prices[i] - min_buy);
            
            // Update the running minimum for future days
            min_buy = min(min_buy, prices[i]);
        }
        
        return max_profit;
    }
};