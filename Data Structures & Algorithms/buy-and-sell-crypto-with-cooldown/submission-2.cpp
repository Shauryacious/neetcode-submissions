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
#include <cstring>

class Solution {
public:
    int maxProfit(vector<int>& p) {
    int dp[5005][2]; // Constraint says prices.length is up to 5000
        int n = p.size();

        // State: 
        // dp[i][holding] = the maximum profit you can achieve starting from day i.
        // 'holding' is 1 if we are currently holding a stock.
        // 'holding' is 0 if we are not holding a stock (meaning we are free to buy).
        
        // Base Case: 
        // If i >= n, we have run out of days to trade.
        // return 0; -> 0 profit can be made from non-existent days.

        memset(dp, -1, sizeof(dp));

        auto f = [&](int i, int holding, auto&& f) -> int {
            // Base case: passed the last day
            if (i >= n) return 0;

            if(dp[i][holding] != -1) return dp[i][holding];
            
            int ans = 0;

            if(holding == 1){ 
                // We are holding a stock, so we can either sell or skip.
                
                // Choice 1: Sell the stock today, then we are forced to cool down (skip next day), move to i + 2 (holding = 0)
                int sell_stock = p[i] + f(i + 2, 0, f); 
                
                // Choice 2: Skip selling today, move to day i + 1 still holding the stock (holding = 1)
                int skip_sell = f(i + 1, 1, f); 

                // Take the maximum of both choices
                ans = max(sell_stock, skip_sell);
            }
            else{ 
                // We don't hold any stock (holding = 0), so we can either buy or skip.
                
                // Choice 1: Buy the stock today, then move to day i + 1 holding the stock (holding = 1)
                int buy_stock = -p[i] + f(i + 1, 1, f); 
                
                // Choice 2: Skip buying today, move to day i + 1 still not holding (holding = 0)
                int skip_buy = f(i + 1, 0, f); 

                // Take the maximum of both choices
                ans = max(buy_stock, skip_buy);
            }

            return dp[i][holding] = ans;
        };

        // Start from day 0, not holding any stock (holding = 0)
        int ans = f(0, 0, f); 
        return ans;
    }
};